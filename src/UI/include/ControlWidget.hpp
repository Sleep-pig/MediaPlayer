#pragma once
#include "Slider.hpp"
#include "audioThread.hpp"
#include "decode.hpp"
#include "playerCommand.hpp"
#include "videoThread.hpp"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <qthread.h>
class ControlWidget : public QWidget {
    Q_OBJECT

private:
    QWidget *sliderWidget{nullptr};
    Slider *slider{nullptr};
    QLabel *timeLabel{nullptr};
    QLabel *totalTimeLabel{nullptr};
    QPushButton *btn{nullptr};
    QMenu *menu{nullptr};


    Decode *decode_th{nullptr};
    VideoThread *video_th{nullptr};
    AudioThread *audio_th{nullptr};
    QThread *decodeThread{nullptr};
    QThread *videoThread{nullptr};
    QThread *audioThread{nullptr};

    int m_type{NONE};

    bool isPlay = false;
    
public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

    const Decode *decodethPtr() { return decode_th; }
    const VideoThread *videothPtr() { return video_th; }
    void showVideo(const QString &path);
    void resumeUI();
    void changePlayState();
};