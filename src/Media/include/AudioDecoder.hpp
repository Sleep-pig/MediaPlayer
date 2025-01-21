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

class AudioDecoder : public QObject {
    friend class Decode;
    Q_OBJECT
signals:
    void sendAudioBuffer(uint8_t *audioBuffer, int bufferSize, double pts);

private:
    AVCodecContext *codecContext{nullptr};
    SwrContext *swrContext{nullptr};

    uint8_t *convertedAudioBuffer{nullptr};

    int audioStreamIndex;

    double time_base_q2d_ms;

    bool packetIsUsed = true;

    void clean();

public:
    AudioDecoder(QObject *parent = nullptr) : QObject(parent) {}

    ~AudioDecoder() = default;

    void decodeAudioPacket(AVPacket *packet);
};
