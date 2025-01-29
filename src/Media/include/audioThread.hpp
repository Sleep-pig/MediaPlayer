#pragma once

#include "AudioDecoder.hpp"
#include "decode.hpp"
#include "libavcodec/packet.h"
#include <QAudioOutput>
#include <QDebug>
#include <QIODevice>
#include <cstdint>
#include <qaudiooutput.h>
#include <qobject.h>
#include <QQueue>
#include <QThread>
#include <qqueue.h>

class AudioThread : public QObject {
    Q_OBJECT
signals:
    void audioDataUsed();

    void audioClockChanged(int pts_seconds);

public slots:

    void onInitAudioOutput(int samplerate, int channels);

    void recvAudioPacket(AVPacket *pkt);
    void recvAudioBuffer(uint8_t *data, int size, double pts);
    void onGetAudioClock(double &pts);

private:
    AudioDecoder *audioDecoder{nullptr};
    QAudioOutput *audioOutput{nullptr};
    QIODevice *outputDevice{nullptr};

    uint8_t *convertedAudioBuffer{nullptr};

    double time_base_q2d{0.0};

    int bytes_per_sec = -1; //  bytes/s

    int lastPtsSec = 0;
    double curPtsMs = 0;

    QQueue<AVPacket *> audioPacketQueue;

     // 输出音频帧
    void outputAudioFrame(uint8_t *audioBuffer, int bufferSize);

    void clean();

public:
    explicit AudioThread(QObject *parent = nullptr);
    ~AudioThread();

    void setAudioDecoder(AudioDecoder *audioDecoder);

};
