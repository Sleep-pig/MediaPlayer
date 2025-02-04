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
signals:
    void startPlay();
    void leftClicked();
    void rightClicked();
    // 全屏请求
    void fullScreenRequest();

private slots:
    // 响应音频进度条
    void onAudioClockChanged(int pts_seconds);

    // 响应拖动进度条, 当鼠标压下时暂停, 并保存播放状态
    void startSeek();

    // 响应拖动进度条, 当鼠标松开时恢复播放状态
    void endSeek();

    // 强制关闭
    void terminatePlay();

    void onPlayOver(); // 播放结束
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

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

    Decode const *decodethPtr() {
        return decode_th;
    }

    VideoThread const *videothPtr() {
        return video_th;
    }

    void showVideo(QString const &path);
    void resumeUI();
    void changePlayState();
};
