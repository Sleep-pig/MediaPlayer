#include "VideoDecoder.hpp"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavcodec/packet.h"
#include "libavutil/error.h"
#include "libavutil/frame.h"
#include "libavutil/hwcontext.h"
#include "libavutil/pixfmt.h"
}
#include <cstdint>
#include <QDebug>
#include <QImage>

void VideoDecoder::clean() {
    hw_device_pix_fmt = AV_PIX_FMT_NONE;

    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
}

void VideoDecoder::decodeVideoPacket(AVPacket *packet) {
    if (avcodec_send_packet(codecContext, packet) == 0) {
        av_packet_free(&packet);
        auto frame = av_frame_alloc();
        int ret = avcodec_receive_frame(codecContext, frame);
        if (ret == 0) {
            double framePts = time_base_q2d_ms * frame->pts;

            if (hw_device_type != AV_HWDEVICE_TYPE_NONE) {
                transferDataFromHW(&frame);
            }

            uint8_t *pixelData = nullptr;
            switch (frame->format) {
            case AV_PIX_FMT_YUV420P:
                pixelData = copyYuv420pData(frame->data, frame->linesize,
                                            frame->width, frame->height);
                break;
            case AV_PIX_FMT_NV12:
                pixelData = copyNv12Data(frame->data, frame->linesize,
                                         frame->width, frame->height);
                break;
            default:
                auto dstFrame = transFrameToDstFmt(
                    frame, frame->width, frame->height, AV_PIX_FMT_YUV410P);
                pixelData = copyYuv420pData(dstFrame->data, dstFrame->linesize,
                                            dstFrame->width, dstFrame->height);
                break;
            }

            emit sendVideoFrame(pixelData, frame->width, frame->height,
                                framePts);
            av_frame_free(&frame);
        } else if (ret != AVERROR(EAGAIN)) {
            qDebug() << "decodeVideoPacket error:" << ret;
        }
    } else {
        qDebug() << "decodeVideoPacket fail";
    }
    packetIsUsed = true;
}

void VideoDecoder::transferDataFromHW(AVFrame **frame) {
    // 如果采用的硬件加速, 解码后的数据还在GPU中,
    // 所以需要通过av_hwframe_transfer_data将GPU中的数据转移到内存中
    // GPU解码数据格式固定为NV12, 来源:
    // https://blog.csdn.net/qq_23282479/article/details/118993650
    AVFrame *tmp_frame = av_frame_alloc();
    if (0 > av_hwframe_transfer_data(tmp_frame, *frame, 0)) {
        qDebug() << "av_hwframe_transfer_data fail";
        av_frame_free(&tmp_frame);
        return;
    }
    av_frame_free(frame);
    if (tmp_frame->format !=
        AV_PIX_FMT_NV12) { // 如果不是NV12格式, 则转换为NV12格式, 临时结构,
                           // 后续再重新梳理
        *frame = transFrameToDstFmt(tmp_frame, tmp_frame->width,
                                    tmp_frame->height, AV_PIX_FMT_NV12);
        av_frame_free(&tmp_frame);
    } else {
        *frame = tmp_frame;
    }
}

uint8_t *
VideoDecoder::copyNv12Data(uint8_t **pixelData,
                           int *linesize, // 属于YUV420空间 因此 Y：UV  2：1
                                          // 一个像素点 包含 一个Y和1/2U或1/2V
                           int pixelWidth, int pixelHeight) {
    uint8_t *pixel = new uint8_t[pixelWidth * pixelHeight * 3 / 2];
    uint8_t *y = pixel;
    uint8_t *uv = pixel + pixelWidth * pixelHeight;

    int halfHeight = pixelHeight >> 1;
    //
    for (int i = 0; i < pixelHeight; i++) {
        memcpy(y + i * pixelWidth, pixelData[0] + i * linesize[0],
               static_cast<size_t>(pixelWidth));
    }
    for (int i = 0; i < halfHeight; i++) {
        memcpy(uv + i * pixelWidth, pixelData[1] + i * linesize[1],
               static_cast<size_t>(pixelWidth));
    }
    return pixel;
}

uint8_t *VideoDecoder::copyYuv420pData(uint8_t **pixelData, int *linesize,
                                       int pixelWidth, int pixelHeight) {
    uint8_t *pixel = new uint8_t[pixelHeight * pixelWidth * 3 / 2];
    int halfWidth = pixelWidth >> 1;
    int halfHeight = pixelHeight >> 1;
    uint8_t *y = pixel;
    uint8_t *u = pixel + pixelWidth * pixelHeight;
    uint8_t *v = pixel + pixelWidth * pixelHeight + halfWidth * halfHeight;
    for (int i = 0; i < pixelHeight; i++) {
        memcpy(y + i * pixelWidth, pixelData[0] + i * linesize[0],
               static_cast<size_t>(pixelWidth));
    }
    for (int i = 0; i < halfHeight; i++) {
        memcpy(u + i * halfWidth, pixelData[1] + i * linesize[1],
               static_cast<size_t>(halfWidth));
    }
    for (int i = 0; i < halfHeight; i++) {
        memcpy(v + i * halfWidth, pixelData[2] + i * linesize[2],
               static_cast<size_t>(halfWidth));
    }
    return pixel;
}

AVFrame *VideoDecoder::transFrameToRGB24(AVFrame *srcFrame, int pixelWidth,
                                         int pixelHeight) {
    AVFrame *frameRGB = av_frame_alloc();
    if (srcFrame->format == AV_PIX_FMT_RGB24) {
        av_frame_copy(frameRGB, srcFrame);
    } else {
        auto swsContext = sws_getContext(
            pixelWidth, pixelHeight, (AVPixelFormat)srcFrame->format,
            pixelWidth, pixelHeight, AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr,
            nullptr, nullptr);

        av_image_alloc(frameRGB->data, frameRGB->linesize, pixelWidth,
                       pixelHeight, AV_PIX_FMT_RGB24, 1);
        sws_scale(swsContext, srcFrame->data, srcFrame->linesize, 0,
                  pixelHeight, frameRGB->data, frameRGB->linesize);

        sws_freeContext(swsContext);
    }
    return frameRGB;
}

AVFrame *VideoDecoder::transFrameToDstFmt(AVFrame *srcFrame, int pixelWidth,
                                          int pixelHeight,
                                          AVPixelFormat dstFormat) {
    AVFrame *dstFrame = av_frame_alloc();
    SwsContext *swsContext = sws_getContext(
        pixelWidth, pixelHeight, AVPixelFormat(srcFrame->format), pixelWidth,
        pixelHeight, dstFormat, SWS_BILINEAR, NULL, NULL, NULL);

    int numBytes =
        av_image_get_buffer_size(dstFormat, pixelWidth, pixelHeight, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    av_image_fill_arrays(dstFrame->data, dstFrame->linesize, buffer, dstFormat,
                         pixelWidth, pixelHeight, 1);

    sws_scale(swsContext, srcFrame->data, srcFrame->linesize, 0, pixelHeight,
              dstFrame->data, dstFrame->linesize);

    dstFrame->format = dstFormat;
    dstFrame->width = pixelWidth;
    dstFrame->height = pixelHeight;
    return dstFrame;
}

int VideoDecoder::writeOneFrame(AVFrame *frame, int pixelWidth, int pixelHeight,
                                QString fileName) {
    if (frame == nullptr) {
        return -1;
    }

    if (frame->format != AV_PIX_FMT_RGB24) {
        AVFrame *frameRGB = transFrameToRGB24(frame, pixelWidth, pixelHeight);
        QImage(frameRGB->data[0], pixelWidth, pixelHeight,
               frameRGB->linesize[0], QImage::Format_RGB888)
            .save(fileName);
        av_frame_free(&frameRGB);
    } else {
        QImage(frame->data[0], pixelWidth, pixelHeight, frame->linesize[0],
               QImage::Format_RGB888)
            .save(fileName);
    }

    return 0;
}
