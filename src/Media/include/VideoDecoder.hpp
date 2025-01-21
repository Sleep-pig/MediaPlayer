#pragma once

#include <qobject.h>
#include <qobjectdefs.h>

extern "C" {
#include "libavcodec/packet.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

class VideoDecoder : public QObject {
    friend class Decode;
    Q_OBJECT
signals:
    void sendVideoFrame(uint8_t *pixelData, int pixelWidth, int pixelHeight,
                        double pts);

private:
    AVCodecContext *codecContext{nullptr};

    AVBufferRef *hw_device_ctx = nullptr;
    enum AVPixelFormat hw_device_pix_fmt = AV_PIX_FMT_NONE;
    enum AVHWDeviceType hw_device_type = AV_HWDEVICE_TYPE_NONE;

    int videoStreamIndex; // 视频流索引

    double time_base_q2d_ms;

    bool packetIsUsed = true;

    void clean();

    // 将硬件解码后的数据拷贝到内存中(但部分数据会消失, 例如pts)
    void transferDataFromHW(AVFrame **frame);

    uint8_t *copyNv12Data(uint8_t **pixelData, int *linesize, int pixelWidth,
                          int pixelHeight);
    uint8_t *copyYuv420pData(uint8_t **pixelData, int *linesize, int pixelWidth,
                             int pixelHeight);

public:
    VideoDecoder(QObject *parent = nullptr) : QObject(parent) {}

    ~VideoDecoder() = default;

    void decodeVideoPacket(AVPacket *packet);

    AVFrame *transFrameToRGB24(AVFrame *frame, int pixelWidth, int pixelHeight);
    AVFrame *transFrameToDstFmt(AVFrame *srcFrame, int pixelWidth,
                                int pixelHeight, AVPixelFormat dstFormat);

    int writeOneFrame(AVFrame *frame, int pixelWidth, int pixelHeight,
                      QString fileName);
};
