#include "MediaPlayer.hpp"
#include "MediaDialog.hpp"
#include <QFileDialog>
#include <qglobal.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <qmainwindow.h>
#include <QPushButton>
#include <QStandardPaths>
#include <qnamespace.h>
#include <qwidget.h>

MediaPlayer::MediaPlayer(QWidget *parent) : QMainWindow(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    w = new MediaDialog(this);
    setCentralWidget(w);
    this->resize(700, 400);

    connect(w->controlWidget->titlebar->getMinimizeLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::showMinimized);
    connect(w->controlWidget->titlebar->getCloseLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::close);
    connect(w->controlWidget->titlebar->getMaximizeLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::showMaximized);

    connect(w, &MediaDialog::startDragging, this,
            &MediaPlayer::handleStartDragging,Qt::DirectConnection);
    connect(w, &MediaDialog::dragging, this, &MediaPlayer::handleDragging,Qt::DirectConnection);

    // w->installEventFilter(this);
}

// bool MediaPlayer::eventFilter(QObject *watched, QEvent *eve) {
//     QMouseEvent *event = static_cast<QMouseEvent *>(eve);
//     if (watched == w) {
//         if (event->pos().y() <= w->controlWidget->titlebar->height()) {
//             if (event->type() == QEvent::MouseButtonPress) {
//                 if (event->button() == Qt::LeftButton) {
//                     mousePressed = true;
//                     mousePoint = event->globalPos() - this->pos();
//                     return true;
//                 }
//             } else if (event->type() == QEvent::MouseButtonRelease) {
//                 mousePressed = false;
//                 return true;
//             } else if (event->type() == QEvent::MouseMove) {
//                 MediaPlayer::move(event->globalPos() - mousePoint);
//                 return true;
//             }
//         }
//     }

//     return QWidget::eventFilter(watched, eve);
// }

MediaPlayer::~MediaPlayer() {}
