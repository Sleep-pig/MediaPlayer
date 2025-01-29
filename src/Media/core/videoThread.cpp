#include "videoThread.hpp"
#include <QDateTime>
#include <QImage>
#include <QPixmap>
#include <QThread>

VideoThread::VideoThread(QObject *parent) : QObject(parent) {}

VideoThread::~VideoThread() {}

void VideoThread::setVideoDecoder(VideoDecoder *decoder) {
    this->decoder = decoder;
    connect(decoder, &VideoDecoder::sendVideoFrame, this,
            &VideoThread::recvVideoFrame);
}

void VideoThread::recvVideoPacket(AVPacket *packet) {
    if (packet != nullptr) {
        decoder->decodeVideoPacket(packet);
    }
}

void VideoThread::recvVideoFrame(uint8_t *data, int pixelWidth, int pixelHeight,
                                 double pts) {
    emit getAudioClock(audioClock);
    int sleepTime = pts - audioClock;
    if (sleepTime > 0 && audioClock >= 0.1) {
        QThread::msleep(sleepTime);
    }
    emit SendFrame(data, pixelWidth, pixelHeight);
}
