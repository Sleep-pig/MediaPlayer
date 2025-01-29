#pragma once

#include "decode.hpp"
#include "VideoDecoder.hpp"
#include <cstdint>
#include <QObject>
#include <qobjectdefs.h>
#include <QQueue>

class VideoThread : public QObject {
    Q_OBJECT
signals:
    void videoDataUsed();

    void videoQueueStatus(int status);

    void SendFrame(uint8_t *pixelData, int pixelWidth, int pixelHeight);

    void getAudioClock(double &pts);

public slots:
    void recvVideoPacket(AVPacket *pkt);
    void recvVideoFrame(uint8_t *data, int pixelWidth, int pixelHeight,
                        double pts);

private:
    VideoDecoder *decoder;
    double audioClock;

public:
    VideoThread(QObject *parent = nullptr);
    ~VideoThread();

    void setVideoDecoder(VideoDecoder *decoder);
};
