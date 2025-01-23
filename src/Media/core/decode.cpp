#include "decode.hpp"
#include "AudioDecoder.hpp"
#include "libavcodec/codec_id.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavutil/buffer.h"
#include "libavutil/hwcontext.h"
#include "libavutil/pixfmt.h"
#include "playerCommand.hpp"
#include <cstdint>
#include <qchar.h>
#include <qdebug.h>
#include <qglobal.h>
#include <QImage>
#include <qlist.h>
#include <QPixmap>

#define MAX_AUDIO_FRAME_SIZE 192000

QString av_get_pixelformat_name(AVPixelFormat format);

Decode::Decode(int const *_type, QObject *parent)
    : QObject(parent),
      formatContext(nullptr),
      mediaType(UNKNOWN),
      m_type(_type) {
    avformat_network_init();
    audioDecoder = new AudioDecoder(this);
    audioDecoder->convertedAudioBuffer =
        (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE);
    videoDecoder = new VideoDecoder(this);

    // 遍历所有支持的硬件类型
    enum AVHWDeviceType print_type = AV_HWDEVICE_TYPE_NONE;
    while ((print_type = av_hwdevice_iterate_types(print_type)) !=
           AV_HWDEVICE_TYPE_NONE) {
        qDebug() << "suport hwdevice: "
                 << av_hwdevice_get_type_name(print_type);
        devices.append(print_type);
    }
}

Decode::~Decode() {
    clean();
    av_free(audioDecoder->convertedAudioBuffer);
}

void Decode::setVideoPath(QString const &filePath) {
    clean();
    if (NO_ERROR == initFFmpeg(filePath)) {
        qDebug() << "init ffmpeg success";
    } else {
        qDebug() << "init ffmpeg fail";
    }
}

int64_t Decode::getAudioFrameCount() const {
    if (audioStreamIndex == -1) {
        return -1;
    }

    int64_t ret = formatContext->streams[audioStreamIndex]->nb_frames;
    qDebug() << "audio frame count:" << ret;
    return ret;
}

int64_t Decode::getVideoFrameCount() const {
    if (videoStreamIndex == -1) {
        return -1;
    }

    int64_t ret = formatContext->streams[videoStreamIndex]->nb_frames;
    qDebug() << "videoFrames:" << ret;
    return ret;
}

int64_t Decode::getDuration() const {
    if (formatContext == nullptr) {
        return -1;
    }

    // 流的总时长 ms
    int64_t duration_ms =
        (formatContext->duration / (int64_t)AV_TIME_BASE / 1000);
    qDebug() << "duration: "
             << QString("%02d:%02d:%02d")
                    .arg(duration_ms / 1000 / 3600)
                    .arg(duration_ms / 1000 / 60 % 60)
                    .arg(duration_ms / 1000 % 60);
    return duration_ms;
}

QList<QString> Decode::getSupportedHwDecoderNames() {
    QList<QString> ret;
    AVBufferRef *hw_device_ctx = nullptr;
    for (auto device: devices) {
        if (av_hwdevice_ctx_create(&hw_device_ctx, device, nullptr, nullptr,
                                   0) < 0) {
            devices.removeOne(device);
            continue;
        }
        av_buffer_unref(&hw_device_ctx);
        QString name = av_hwdevice_get_type_name(device);
        ret.append(name);
        qDebug() << "avaliable hw device:" << name;
    }
    return ret;
}

bool Decode::resume() {
    if (formatContext == nullptr) {
        return false;
    }

    clearPacketQueue();
    av_seek_frame(formatContext, -1, 0, AVSEEK_FLAG_BACKWARD);
    return true;
}

void Decode::setCurFrame(int64_t curPts_s) {
    if (formatContext == nullptr) {
        return;
    }

    clearPacketQueue();
    int curPts_ms = curPts_s * 1000;
    int64_t timestamp = curPts_ms / defalt_time_base_q2d_ms;
    av_seek_frame(formatContext, defaltStreamIndex, timestamp,
                  AVSEEK_FLAG_BACKWARD);
}

int Decode::initFFmpeg(QString const &filePath) {
    try {
        formatContext = avformat_alloc_context();
        if (avformat_open_input(&formatContext, filePath.toStdString().c_str(),
                                nullptr, nullptr) != 0) {
            throw OPEN_STREAM_ERROR;
        }

        if (avformat_find_stream_info(formatContext, nullptr) < 0) {
            throw FIND_INFO_ERROR;
        }

        audioStreamIndex = initAudioDecoder();
        videoStreamIndex = initVideoDecoder(devices);
        qDebug() << "audioStreamIndex:" << audioStreamIndex
                 << "videoStreamIndex:" << videoStreamIndex;
        if (audioStreamIndex == -1 && videoStreamIndex == -1) {
            throw FIND_STREAM_ERROR;
        }

        if (audioStreamIndex == -1) {
            mediaType = ONLY_VIDEO;
        } else if (videoStreamIndex == -1 ||
                   formatContext->streams[audioStreamIndex]
                           ->codecpar->codec_id == AV_CODEC_ID_MP3) {
            mediaType = ONLY_AUDIO;
        } else {
            mediaType = MULTI_AUDIO_VIDEO;
        }

        defaltStreamIndex =
            (mediaType == ONLY_AUDIO) ? audioStreamIndex : videoStreamIndex;
        defalt_time_base_q2d_ms = (mediaType == ONLY_AUDIO)
                                      ? audioDecoder->time_base_q2d_ms
                                      : videoDecoder->time_base_q2d_ms;

    } catch (FFMPEG_INIT_ERROR err) {
        clean();
        debugError(err);
        return err;
    }
    return NO_ERROR;
}

int Decode::initAudioDecoder() {
    auto &audioCodecContext = audioDecoder->codecContext;
    auto &swrContext = audioDecoder->swrContext;
    auto &audioStreamIndex = audioDecoder->audioStreamIndex;
    auto &time_base_q2d_ms = audioDecoder->time_base_q2d_ms;

    AVCodec const *audioCodec = nullptr;
    // 找到指定流类型的流信息，并且初始化codec(如果codec没有值)，返回流索引
    audioStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO,
                                           -1, -1, &audioCodec, 0);

    if (audioStreamIndex == AVERROR_STREAM_NOT_FOUND) {
        return -1;
    } else if (audioStreamIndex == AVERROR_DECODER_NOT_FOUND) {
        throw FIND_AUDIO_DECODER_ERROR;
    }

    if (initCodec(&audioCodecContext, audioStreamIndex, audioCodec) < 0) {
        throw INIT_AUDIO_CODEC_CONTEXT_ERROR;
    }

    // Initialize resampler context
    // 错误时, SwrContext 将被释放 并且 *ps(即传入的swrContext) 被置为空
    if (0 != swr_alloc_set_opts2(
                 &swrContext, &audioCodecContext->ch_layout, AV_SAMPLE_FMT_S16,
                 audioCodecContext->sample_rate, &audioCodecContext->ch_layout,
                 audioCodecContext->sample_fmt, audioCodecContext->sample_rate,
                 0, nullptr)) {
        throw INIT_RESAMPLER_CONTEXT_ERROR;
    }

    if (!swrContext || swr_init(swrContext) < 0) {
        throw INIT_SW_RENDERER_CONTEXT;
    }

    time_base_q2d_ms =
        av_q2d(formatContext->streams[audioStreamIndex]->time_base) * 1000;

    // 音频压缩编码格式
    if (AV_CODEC_ID_AAC == audioCodecContext->codec_id) {
        qDebug() << "audio codec:AAC";
    } else if (AV_CODEC_ID_MP3 == audioCodecContext->codec_id) {
        qDebug() << "audio codec:MP3";
    } else {
        qDebug() << "audio codec:other; value: " << audioCodecContext->codec_id;
    }

    emit initAudioOutput(audioDecoder->codecContext->sample_rate,
                         audioDecoder->codecContext->ch_layout.nb_channels);
    return audioStreamIndex;
}

int Decode::initVideoDecoder(QList<AVHWDeviceType> &devices) {
    auto &videoCodecContext = videoDecoder->codecContext;
    auto &videoStreamIndex = videoDecoder->videoStreamIndex;
    auto &time_base_q2d_ms = videoDecoder->time_base_q2d_ms;
    auto &hw_device_ctx = videoDecoder->hw_device_ctx;
    auto &hw_device_pix_fmt = videoDecoder->hw_device_pix_fmt;
    auto &hw_device_type = videoDecoder->hw_device_type;

    AVCodec const *videoCodec = nullptr;
    // 找到指定流类型的流信息，并且初始化codec(如果codec没有值)，返回流索引
    videoStreamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO,
                                           -1, -1, &videoCodec, 0);
    if (videoStreamIndex == AVERROR_STREAM_NOT_FOUND) {
        return -1;
    } else if (videoStreamIndex == AVERROR_DECODER_NOT_FOUND) {
        throw FIND_VIDEO_DECODER_ERROR;
    }

    // 根据解码器获取支持此解码方式的硬件加速计
    // 所有支持的硬件解码器保存在AVCodec的hw_configs变量中。对于硬件编码器来说又是单独的AVCodec
    if (!devices.isEmpty()) {
        initHwdeviceCtx(
            videoCodec,
            formatContext->streams[videoStreamIndex]->codecpar->width, devices,
            hw_device_pix_fmt, hw_device_type, &hw_device_ctx);
    }

    if (initCodec(&videoCodecContext, videoStreamIndex, videoCodec) < 0) {
        throw INIT_VIDEO_CODEC_CONTEXT_ERROR;
    }

    time_base_q2d_ms =
        av_q2d(formatContext->streams[videoStreamIndex]->time_base) * 1000;

    if (AV_CODEC_ID_H264 == videoCodec->id) {
        qDebug() << "video codec:H264";
    } else if (AV_CODEC_ID_HEVC == videoCodec->id) {
        qDebug() << "video codec:HEVC";
    } else {
        qDebug() << "video codec:other; value: " << videoCodec->id;
    }

    emit initVideoOutput(videoDecoder->hw_device_type);
    return videoStreamIndex;
}

void Decode::initHwdeviceCtx(AVCodec const *videoCodec, int videoWidth,
                             QList<AVHWDeviceType> &devices,
                             AVPixelFormat &hw_device_pix_fmt,
                             AVHWDeviceType &hw_device_type,
                             AVBufferRef **hw_device_ctx) {
    AVCodecHWConfig const *config = nullptr; // 硬解码器
    for (int i = 0;; i++) {
        config = avcodec_get_hw_config(videoCodec, i);
        if (config == nullptr) {
            break;
        }

        // 可能一个解码器对应着多个硬件加速方式，所以这里将其挑选出来
        if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
            devices.contains(config->device_type) &&
            config->pix_fmt != AV_PIX_FMT_NONE) {
            qDebug() << "config->pix_fmt: "
                     << av_get_pixelformat_name(config->pix_fmt);
            qDebug() << "config->device_type: "
                     << av_hwdevice_get_type_name(config->device_type);

            if (config->pix_fmt == AV_PIX_FMT_CUDA &&
                videoWidth >
                    2032) { // cuda硬解暂时不支持4k, 有bug不会处理,待后续学习
                qDebug() << "CUDA only support width <= 2032";
                continue;
            }

            if (av_hwdevice_ctx_create(hw_device_ctx, config->device_type,
                                       nullptr, nullptr, 0) < 0) {
                devices.removeOne(config->device_type);
            } else {
                hw_device_pix_fmt = config->pix_fmt;
                hw_device_type = config->device_type;
                break;
            }
        } else {
            qDebug() << "unuseful config->device_type: "
                     << av_hwdevice_get_type_name(config->device_type);
        }
    }
}

int Decode::initCodec(AVCodecContext **codecContext, int streamIndex,
                      AVCodec const *codec) {
    *codecContext = avcodec_alloc_context3(codec);
    AVStream *stream = formatContext->streams[streamIndex];

    avcodec_parameters_to_context(*codecContext, stream->codecpar);

    // 如果是视频流，并且支持硬件加速，则设置硬件加速
    if (formatContext->streams[streamIndex]->codecpar->codec_type ==
            AVMEDIA_TYPE_VIDEO &&
        videoDecoder->hw_device_type != AV_HWDEVICE_TYPE_NONE &&
        videoDecoder->hw_device_ctx != nullptr) {
        (*codecContext)->opaque = &this->videoDecoder->hw_device_pix_fmt;
        (*codecContext)->get_format = getHwFormat;
        (*codecContext)->hw_device_ctx =
            av_buffer_ref(videoDecoder->hw_device_ctx);
        av_buffer_unref(&videoDecoder->hw_device_ctx);
    }
    qDebug() << "(*codecContext)->codec_id: " << (*codecContext)->codec_id;
    return avcodec_open2(*codecContext, codec, nullptr);
}

void Decode::clean() {
    clearPacketQueue();
    mediaType = UNKNOWN;

    audioDecoder->clean();
    videoDecoder->clean();

    if (formatContext) {
        avformat_close_input(&formatContext);
        avformat_free_context(formatContext);
        formatContext = nullptr;
    }
}

void Decode::clearPacketQueue() {
    if (videoDecoder && videoDecoder->codecContext) {
        avcodec_flush_buffers(videoDecoder->codecContext);
    }

    audioDecoder->packetIsUsed = true;
    videoDecoder->packetIsUsed = true;
    while (!audioPacketQueue.isEmpty()) {
        auto packet = audioPacketQueue.dequeue();
        av_packet_free(&packet);
    }
    while (!videoPacketQueue.isEmpty()) {
        auto packet = videoPacketQueue.dequeue();
        av_packet_free(&packet);
    }
}

void Decode::decodePacket() {
    if (*m_type != CONTL_TYPE::PLAY) {
        return;
    }

    try {
        switch (mediaType) {
        case ONLY_VIDEO:        decodeVideo(); break;
        case ONLY_AUDIO:        decodeAudio(); break;
        case MULTI_AUDIO_VIDEO: decodeMultMedia(); break;
        default:                throw (int)CONTL_TYPE::END;
        }
    } catch (int controlType) {
        if (controlType == CONTL_TYPE::END) {
            emit playOver();
        }
        debugPlayerCommand(CONTL_TYPE(controlType));
    }
}

void Decode::decodeAudio() {
    while (*m_type == CONTL_TYPE::PLAY) {
        while (audioDecoder->packetIsUsed == false) {
            if (*m_type != CONTL_TYPE::PLAY) {
                throw *m_type;
            }
            QThread::msleep(10);
        }

        AVPacket *packet = av_packet_alloc();
        if (av_read_frame(formatContext, packet) < 0) {
            throw (int)CONTL_TYPE::END;
        }
        if (packet->stream_index == audioStreamIndex) {
            audioDecoder->packetIsUsed = false;
            emit sendAudioPacket(packet);
        } else {
            qDebug() << "unknow stream index: " << packet->stream_index;
            av_packet_free(&packet);
        }
    }
}

void Decode::decodeVideo() {}

void Decode::decodeMultMedia() {
    while (*m_type == CONTL_TYPE::PLAY) {
        while (audioDecoder->packetIsUsed == false &&
               videoDecoder->packetIsUsed == false) {
            if (*m_type != CONTL_TYPE::PLAY) {
                throw *m_type;
            }
            QThread::msleep(10);
        }

        if (audioDecoder->packetIsUsed) {
            AVPacket *packet = nullptr;
            if (!audioPacketQueue.isEmpty()) {
                packet = audioPacketQueue.dequeue();
            } else {
                packet = av_packet_alloc();
                if (av_read_frame(formatContext, packet) < 0) {
                    throw (int)CONTL_TYPE::END;
                }
            }

            if (packet->stream_index == audioStreamIndex) {
                // qDebug() << "audioStreamIndex, packet->pts: " <<
                // audioDecoder->time_base_q2d_ms * packet->pts;
                audioDecoder->packetIsUsed = false;
                emit sendAudioPacket(packet);
            } else if (packet->stream_index == videoStreamIndex) {
                videoPacketQueue.enqueue(packet);
            } else {
                qDebug() << "in audio unknow stream index: "
                         << packet->stream_index;
                av_packet_free(&packet);
            }
        }
        if (videoDecoder->packetIsUsed) {
            AVPacket *packet = nullptr;
            if (!videoPacketQueue.isEmpty()) {
                packet = videoPacketQueue.dequeue();
            } else {
                packet = av_packet_alloc();
                if (av_read_frame(formatContext, packet) < 0) {
                    throw (int)CONTL_TYPE::END;
                }
            }

            if (packet->stream_index == videoStreamIndex) {
                // qDebug() << "videoStreamIndex, packet->pts: " <<
                // videoDecoder->time_base_q2d_ms * packet->pts;

                videoDecoder->packetIsUsed = false;
                emit sendVideoPacket(packet);
            } else if (packet->stream_index == audioStreamIndex) {
                audioPacketQueue.enqueue(packet);
            } else {
                qDebug() << "in video unknow stream index: "
                         << packet->stream_index;
                av_packet_free(&packet);
            }
        }
    }
}

AVPixelFormat Decode::getHwFormat(AVCodecContext *ctx,
                                  AVPixelFormat const *pix_fmts) {
    const enum AVPixelFormat *p;
    AVPixelFormat hw_device_pix_fmt =
        *(static_cast<AVPixelFormat *>(ctx->opaque));
    for (p = pix_fmts; *p != AV_PIX_FMT_NONE; p++) {
        if (*p == hw_device_pix_fmt) {
            return *p;
        }
    }

    qDebug() << "Failed to get HW surface format.";
    return AV_PIX_FMT_NONE;
}

void Decode::debugError(FFMPEG_INIT_ERROR error) {
    switch (error) {
    case FFMPEG_INIT_ERROR::OPEN_STREAM_ERROR:
        qDebug() << "open stream error";
        break;
    case FFMPEG_INIT_ERROR::FIND_INFO_ERROR:
        qDebug() << "find info error";
        break;
    case FFMPEG_INIT_ERROR::FIND_STREAM_ERROR:
        qDebug() << "find stream error";
        break;
    case FFMPEG_INIT_ERROR::INIT_VIDEO_CODEC_CONTEXT_ERROR:
        qDebug() << "init video codec context error";
        break;
    case FFMPEG_INIT_ERROR::INIT_AUDIO_CODEC_CONTEXT_ERROR:
        qDebug() << "init audio codec context error";
        break;
    case FFMPEG_INIT_ERROR::INIT_RESAMPLER_CONTEXT_ERROR:
        qDebug() << "init resampler context error";
        break;
    case FFMPEG_INIT_ERROR::INIT_SW_RENDERER_CONTEXT:
        qDebug() << "init sw renderer context error";
        break;
    default: break;
    }
}

QString av_get_pixelformat_name(AVPixelFormat format) {
    QString name;
    switch (format) {
    case AV_PIX_FMT_NONE:         name = "AV_PIX_FMT_NONE"; break;
    case AV_PIX_FMT_YUV420P:      name = "AV_PIX_FMT_YUV420P"; break;
    case AV_PIX_FMT_NV12:         name = "AV_PIX_FMT_NV12"; break;
    case AV_PIX_FMT_VAAPI:        name = "AV_PIX_FMT_VAAPI"; break;
    case AV_PIX_FMT_VIDEOTOOLBOX: name = "AV_PIX_FMT_VIDEOTOOLBOX"; break;
    case AV_PIX_FMT_MEDIACODEC:   name = "AV_PIX_FMT_MEDIACODEC"; break;
    case AV_PIX_FMT_D3D11:        name = "AV_PIX_FMT_D3D11"; break;
    case AV_PIX_FMT_OPENCL:       name = "AV_PIX_FMT_OPENCL"; break;
    case AV_PIX_FMT_VULKAN:       name = "AV_PIX_FMT_VULKAN"; break;
    //case AV_PIX_FMT_D3D12:        name = "AV_PIX_FMT_D3D12"; break;
    case AV_PIX_FMT_DXVA2_VLD:    name = "AV_PIX_FMT_DXVA2_VLD"; break;
    case AV_PIX_FMT_VDPAU:        name = "AV_PIX_FMT_VDPAU"; break;
    case AV_PIX_FMT_QSV:          name = "AV_PIX_FMT_QSV"; break;
    case AV_PIX_FMT_MMAL:         name = "AV_PIX_FMT_MMAL"; break;
    case AV_PIX_FMT_D3D11VA_VLD:  name = "AV_PIX_FMT_D3D11VA_VLD"; break;
    case AV_PIX_FMT_CUDA:         name = "AV_PIX_FMT_CUDA"; break;

    default: name = "value:" + QString::number(format); break;
    }
    return name;
}
