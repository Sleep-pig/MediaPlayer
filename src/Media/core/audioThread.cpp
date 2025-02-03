#include "audioThread.hpp"
#include <qaudiodeviceinfo.h>
#include <qaudioformat.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qthread.h>

#define MAX_AUDIO_FRAME_SIZE 192000

AudioThread::AudioThread(QObject *parent) : QObject(parent) {}

AudioThread::~AudioThread() {
    clean();
}

void AudioThread::setAudioDecoder(AudioDecoder *audioDecoder) {
    this->audioDecoder = audioDecoder;
    connect(audioDecoder, &AudioDecoder::sendAudioBuffer, this,
            &AudioThread::recvAudioBuffer);
}

void AudioThread::onInitAudioOutput(int samplerate, int channels) {
    clean();
    bytes_per_sec = samplerate * channels * 2;

    QAudioFormat format;
    format.setSampleRate(samplerate);
    format.setChannelCount(channels);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }

    audioOutput = new QAudioOutput(format);
    outputDevice = audioOutput->start();
}

void AudioThread::onGetAudioClock(double &pts) {
    if (audioOutput == nullptr) {
        return;
    }

    // 输出流中未播放数据大小
    int buf_size = audioOutput->bufferSize();

    // 当前时间戳 - 输出流中缓存数据 可播放时长    //当前音频播放到哪里
    pts = (curPtsMs - static_cast<double>(buf_size) / bytes_per_sec);
}

void AudioThread::recvAudioPacket(AVPacket *packet) {
    if (packet != nullptr && audioOutput != nullptr) {
        audioDecoder->decodeAudioPacket(packet);
    }
}

void AudioThread::recvAudioBuffer(uint8_t *data, int size, double pts) {
    curPtsMs = pts;
    int curPtsSec = pts / 1000;
    while (audioOutput->bytesFree() < size) {
        QThread::msleep(10);
    }

    if (curPtsSec != lastPtsSec) {
        lastPtsSec = curPtsSec;
        emit audioClockChanged(curPtsSec);
    }
    outputAudioFrame(data, size);
}

void AudioThread::outputAudioFrame(uint8_t *audioBuffer, int bufferSize) {
    outputDevice->write(reinterpret_cast<char const *>(audioBuffer),
                        bufferSize);
}

void AudioThread::clean() {
    if (audioOutput) {
        audioOutput->stop();
        outputDevice = nullptr;
        audioOutput->deleteLater();
        audioOutput = nullptr;

        bytes_per_sec = -1;

        lastPtsSec = 0;
        curPtsMs = 0;
    }
}
