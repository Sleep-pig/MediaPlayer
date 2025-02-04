#include "ControlWidget.hpp"
#include "ClickedLabel.hpp"
#include "TitleWidget.hpp"
#include <qapplication.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include <QFileDialog>
#include <qglobal.h>
#include <qlabel.h>
#include <QMouseEvent>
#include <qpushbutton.h>
#include <QStandardPaths>
#include <qwidget.h>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);

    // 添加标题栏组
    titlebar = new TitleWidget(this);
    titlebar->setFixedHeight(30);
    layout->addWidget(titlebar);

    // 连接槽, 选择视频并播放
    connect(titlebar->getSelectedButton(), &QPushButton::clicked, this,
            &ControlWidget::onslectPlay);

    layout->addStretch(); // 添加弹簧 将进度条挤下面

    // 添加进度条组（包括时间 将来的声音调整 快放等）
    {
        sliderWidget = new QWidget(this);
        layout->addWidget(sliderWidget);
        QHBoxLayout *sliderLayout = new QHBoxLayout(
            sliderWidget); // 将来的其他部件就可以添加到这个水平布局中
        sliderWidget->setLayout(sliderLayout);
        sliderLayout->setContentsMargins(0, 0, 0, 0);
        // 添加开始时间label
        timeLabel = new QLabel("", sliderWidget);
        timeLabel->setStyleSheet("color: black;");
        sliderLayout->addWidget(timeLabel);

        slider = new Slider(Qt::Horizontal, sliderWidget);
        slider->setValue(0);
        slider->setRange(0, 0);
        sliderLayout->addWidget(slider);

        totalTimeLabel = new QLabel("", sliderWidget);
        totalTimeLabel->setStyleSheet("color: black;");
        sliderLayout->addWidget(totalTimeLabel);

        btn = new QPushButton("test", sliderWidget);
        btn->setStyleSheet("background-color: white;");
        sliderLayout->addWidget(btn);
        sliderWidget->setStyleSheet("background-color: rgb(237, 218, 218);");
    }

    decode_th = new Decode(&m_type);
    decodeThread = new QThread();
    decode_th->moveToThread(decodeThread);
    decodeThread->start();
    connect(this, &ControlWidget::startPlay, decode_th, &Decode::decodePacket);
    connect(decode_th, &Decode::playOver, this, &ControlWidget::onPlayOver);

    audio_th = new AudioThread();
    audio_th->setAudioDecoder(decode_th->getAudioDecoder());
    audioThread = new QThread();
    audio_th->moveToThread(audioThread);
    audioThread->start();
    connect(decode_th, &Decode::initAudioOutput, audio_th,
            &AudioThread::onInitAudioOutput, Qt::DirectConnection);
    connect(decode_th, &Decode::sendAudioPacket, audio_th,
            &AudioThread::recvAudioPacket);
    connect(audio_th, &AudioThread::audioClockChanged, this,
            &ControlWidget::onAudioClockChanged);

    video_th = new VideoThread();
    video_th->setVideoDecoder(decode_th->getVideoDecoder());
    videoThread = new QThread();
    video_th->moveToThread(videoThread);
    videoThread->start();
    connect(decode_th, &Decode::sendVideoPacket, video_th,
            &VideoThread::recvVideoPacket);
    connect(video_th, &VideoThread::getAudioClock, audio_th,
            &AudioThread::onGetAudioClock, Qt::DirectConnection); // 必须直连

    // slider拖动
    connect(slider, &Slider::sliderClicked, this, &ControlWidget::startSeek);
    connect(slider, &Slider::sliderMoved, decode_th, &Decode::setCurFrame);
    connect(slider, &Slider::sliderReleased, this, &ControlWidget::endSeek);
}

ControlWidget::~ControlWidget() {
    terminatePlay();

    decode_th->deleteLater();
    audio_th->deleteLater();
    video_th->deleteLater();

    decodeThread->quit();
    decodeThread->wait();
    decodeThread->deleteLater();

    audioThread->quit();
    audioThread->wait();
    audioThread->deleteLater();

    videoThread->quit();
    videoThread->wait();
    videoThread->deleteLater();

    qDebug() << "ControlWidget::~ControlWidget()";
}

void ControlWidget::showVideo(QString const &path) {
    if (m_type != CONTL_TYPE::NONE) {
        terminatePlay();
        slider->setValue(0);
        timeLabel->setText("00:00");
        totalTimeLabel->setText("00:00");
        QApplication::instance()->processEvents(); // 强制更新UI
        QThread::msleep(100);
    }
    decode_th->setVideoPath(path);

    int64_t duration_ms = decode_th->getDuration();
    int duration_s = static_cast<int>(duration_ms / 1000);
    slider->setRange(0, duration_s);
    if (duration_s > 3600) {
        totalTimeLabel->setText(
            QString::asprintf("%02d:%02d:%02d", duration_s / 3600,
                              duration_s / 60 % 60, duration_s % 60));
    } else {
        totalTimeLabel->setText(QString::asprintf(
            "%02d:%02d", duration_s / 60 % 60, duration_s % 60));
    }
    m_type = CONTL_TYPE::PLAY;
    emit ControlWidget::startPlay();
}

void ControlWidget::resumeUI() {
    slider->setValue(0);
    timeLabel->setText("00:00");
}

void ControlWidget::onAudioClockChanged(int pts_seconds) {
    slider->setValue(pts_seconds);
    QString pts_str;
    if (pts_seconds > 3600) {
        pts_str = QString::asprintf("%02d:%02d:%02d", pts_seconds / 3600,
                                    pts_seconds / 60 % 60, pts_seconds % 60);
    } else {
        pts_str = QString::asprintf("%02d:%02d", pts_seconds / 60 % 60,
                                    pts_seconds % 60);
    }

    timeLabel->setText(pts_str);
}

void ControlWidget::onslectPlay() {
    QString path = QFileDialog::getOpenFileName(
        this, "选择视频文件",
        QStandardPaths::writableLocation(
            QStandardPaths::StandardLocation::MoviesLocation),
        "Media Files(*.mp4 *.avi *.mkv *.mp3 *.wav);;All Files(*)");
    if (!path.isEmpty()) {
        // 仅显示文件名, 并且去掉后缀
        titlebar->getTitle()->setText(
            path.mid(path.lastIndexOf("/") + 1,
                     path.lastIndexOf(".") - path.lastIndexOf("/") - 1));
        showVideo(path);
    }
}

void ControlWidget::startSeek() {
    isPlay = (m_type == CONTL_TYPE::PLAY);
    m_type = CONTL_TYPE::PAUSE;
}

void ControlWidget::endSeek() {
    m_type = (isPlay ? CONTL_TYPE::PLAY : CONTL_TYPE::PAUSE);
    emit ControlWidget::startPlay();
}

void ControlWidget::changePlayState() {
    switch (m_type) {
    case CONTL_TYPE::END:
        resumeUI();
        m_type = CONTL_TYPE::RESUME;
        break;

    case CONTL_TYPE::PLAY: m_type = CONTL_TYPE::PAUSE; break;

    case CONTL_TYPE::PAUSE: m_type = CONTL_TYPE::PLAY; break;

    case CONTL_TYPE::STOP:
    case CONTL_TYPE::RESUME:
        decode_th->resume();
        m_type = CONTL_TYPE::PLAY;
        break;

    default: break;
    }
    emit ControlWidget::startPlay();
    debugPlayerCommand((CONTL_TYPE)m_type);
}

void ControlWidget::terminatePlay() {
    m_type = CONTL_TYPE::STOP;
}

void ControlWidget::onPlayOver() {
    m_type = CONTL_TYPE::END;
    slider->setValue(slider->maximum());
    timeLabel->setText(totalTimeLabel->text());
}

void ControlWidget::mousePressEvent(QMouseEvent *event) {
    if (event->pos().x() >= 0 && event->pos().x() <= width() &&
        event->pos().y() >= titlebar->height() &&
        event->pos().y() <= height() - sliderWidget->height()) {
        if (event->button() == Qt::LeftButton) {
            changePlayState();
        }
    }
    QWidget::mousePressEvent(event);
}

