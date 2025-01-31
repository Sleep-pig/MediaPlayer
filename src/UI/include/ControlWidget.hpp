#pragma once
#include "audioThread.hpp"
#include "decode.hpp"
#include "playerCommand.hpp"
#include "Slider.hpp"
#include "videoThread.hpp"
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <qthread.h>
#include <QWidget>

class ControlWidget : public QWidget {
    Q_OBJECT

    friend class ShowWidget;

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

    Decode const *decodethPtr() {
        return decode_th;
    }

    VideoThread const *videothPtr() {
        return video_th;
    }

    // void showVideo(const QString &path);
    // void resumeUI();
    // void changePlayState();
};
