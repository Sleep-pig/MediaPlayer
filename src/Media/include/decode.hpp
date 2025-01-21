#pragma once

#include <cstdint>
#include <QAudioOutput>
#include <QDebug>
#include <QIODevice>
#include <QMetaType>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qqueue.h>
#include <QQueue>
#include <QThread>

extern "C" {
#include "libavcodec/packet.h"
#include "libavutil/hwcontext.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

class AudioDecoder;
class VideoDecoder;

#ifndef QMETATYPEID_DECODER
# define QMETATYPEID_DECODER
Q_DECLARE_METATYPE(AudioDecoder *);
Q_DECLARE_METATYPE(VideoDecoder *);
#endif

class Decode : public QObject {
    Q_OBJECT
signals:
    void startPlay();
    void playOver();

    void initAudioOutput();
    void initVideoOutput();

    void sendAudioPacket(AVPacket *pkt);
    void sendVideoPacket(AVPacket *pkt);

public slots:
    // 响应拖动进度条，跳转帧并且返回画面
    void setCurFrame(int64_t _curFrame);

    // 开始播放
    void decodePacket();

public:
    enum FFMPEG_INIT_ERROR {
        NO_ERROR = 0,
        OPEN_STREAM_ERROR,
        FIND_INFO_ERROR,
        FIND_STREAM_ERROR,
        FIND_AUDIO_DECODER_ERROR,
        FIND_VIDEO_DECODER_ERROR,
        INIT_AUDIO_CODEC_CONTEXT_ERROR,
        INIT_VIDEO_CODEC_CONTEXT_ERROR,
        INIT_RESAMPLER_CONTEXT_ERROR,
        INIT_SW_RENDERER_CONTEXT,
    };

    enum FFMPEG_MEDIA_TYPE {
        UNKNOWN,
        ONLY_AUDIO,
        ONLY_VIDEO,
        MULTI_AUDIO_VIDEO,
    };

private:
    QList<AVHWDeviceType> devices;  // 设备支持的硬解码器
    AVFormatContext *formatContext; // 解封装上下文

    AudioDecoder *audioDecoder{nullptr};
    VideoDecoder *videoDecoder{nullptr};

    QQueue<AVPacket *> audioPacketQueue;
    QQueue<AVPacket *> videoPacketQueue;

    FFMPEG_MEDIA_TYPE mediaType;

    int audioStreamIndex;
    int videoStreamIndex;  // 视频流索引
    int defaltStreamIndex; // 默认流索引
    double defalt_time_base_q2d_ms;

    int const *m_type; // 控制播放状态

    // 初始化
    int initFFmpeg(QString const &filePath);

    // 音频相关结构体初始化, 成功返回audioStreamIndex, 无音频流返回-1,
    // 失败抛出FFMPEG_INIT_ERROR
    int initAudioDecoder();
    // 视频相关结构体初始化, 成功返回videoStreamIndex, 无视频流返回-1,
    // 失败抛出FFMPEG_INIT_ERROR
    int initVideoDecoder(QList<AVHWDeviceType> &devices);
    // 硬解所需相关
    void initHwdeviceCtx(AVCodec const *videoCodec, int videoWidth,
                         QList<AVHWDeviceType> &devices,
                         AVPixelFormat &hw_device_pix_fmt,
                         AVHWDeviceType &hw_device_type,
                         AVBufferRef **hw_device_ctx);

    // AVCodecContext *getCudaDecoder
    int initCodec(AVCodecContext **codecContext, int videoStreamIndex,
                  AVCodec const *codec);

    void clean();
    void clearPacketQueue();

    void debugError(FFMPEG_INIT_ERROR error);

    static AVPixelFormat getHwFormat(AVCodecContext *ctx,
                                     const enum AVPixelFormat *pix_fmts);

    void decodeAudio();
    void decodeVideo();
    void decodeMultMedia();

public:
    explicit Decode(int const *_type, QObject *parent = nullptr);
    ~Decode();

    void setVideoPath(QString const &filePath);

    bool resume();

    AudioDecoder *getAudioDecoder() const {
        return audioDecoder;
    }

    VideoDecoder *getVideoDecoder() const {
        return videoDecoder;
    }

    // 得到总音频帧数
    int64_t getAudioFrameCount() const;
    // 得到总视频帧数
    int64_t getVideoFrameCount() const;
    // 得到总时长
    int64_t getDuration() const;

    // 获取支持的硬解码器
    QList<QString> getSupportedHwDecoderNames();
};



