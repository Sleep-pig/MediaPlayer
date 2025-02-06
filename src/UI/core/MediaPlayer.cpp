#include "MediaPlayer.hpp"
#include "MediaDialog.hpp"
#include <QFileDialog>
#include <qglobal.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <QPushButton>
#include <QStandardPaths>
#include <qwidget.h>

MediaPlayer::MediaPlayer(QWidget *parent) : QMainWindow(parent) {
    setAttribute(Qt::WA_Hover);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    w = new MediaDialog(this);
    setCentralWidget(w);
    this->resize(700, 400);
    this->setMinimumSize(300, 130);
    this->setContentsMargins(5, 5, 5, 5);
    connect(w->controlWidget->titlebar->getMinimizeLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::showMinimized);
    connect(w->controlWidget->titlebar->getCloseLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::close);
    connect(w->controlWidget->titlebar->getMaximizeLb(), &ClickedLabel::clicked,
            this, &MediaPlayer::showMaximized);
}

MediaPlayer::~MediaPlayer() {}

MEdge MediaPlayer::calculateEdge(QPoint const &pos) {
    MEdge edge{MEdge::None};
    int x = pos.x();
    int y = pos.y();

    if ((x > m_borderPixel && x <= width() - m_borderPixel) &&
        (y > m_borderPixel &&
         y <= w->controlWidget->titlebar->height() + m_borderPixel)) {
        edge = MEdge::Title;
    }

    if (x >= width() - m_borderPixel && x <= width() &&
        y >= height() - m_borderPixel && y <= height()) {
        edge = MEdge::BottomRight;
    }
    if (x >= width() - m_borderPixel && x <= width() && y >= 0 &&
        y <= m_borderPixel) {
        edge = MEdge::TopRight;
    }
    if (x >= 0 && x <= m_borderPixel && y >= height() - m_borderPixel &&
        y <= height()) {
        edge = MEdge::BottomLeft;
    }
    if (x >= 0 && x <= m_borderPixel && y >= 0 && y <= m_borderPixel) {
        edge = MEdge::TopLeft;
    }

    if (y >= 0 && y <= m_borderPixel) {
        edge = MEdge::Top;
    } else if (y >= height() - m_borderPixel && y <= height()) {
        edge = MEdge::Bottom;
    }
    if (x >= 0 && x <= m_borderPixel) {
        edge = MEdge::Left;
    } else if (x >= width() - m_borderPixel && x <= width()) {
        edge = MEdge::Right;
    }
    return edge;
}

void MediaPlayer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_edge = calculateEdge(event->pos());
        m_isDragging = m_edge != MEdge::None;
        if (m_isDragging) {
            m_dragStartPosition = event->globalPos();
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        }
    }
    QWidget::mousePressEvent(event);
}

void MediaPlayer::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging) {
        if (m_edge == MEdge::Title) {
            QPoint new_pos = event->globalPos() - m_dragPosition;
            move(new_pos);
            return;
        }

        // 拖拽调整窗口大小
        QPoint delta = event->globalPos() - m_dragStartPosition;
        QRect newGeometry = geometry();
        if (m_edge == MEdge::Top) {
            newGeometry.setTop(newGeometry.top() + delta.y());
        }
        if (m_edge == MEdge::Bottom) {
            newGeometry.setBottom(newGeometry.bottom() + delta.y());
        }
        if (m_edge == MEdge::Left) {
            newGeometry.setLeft(newGeometry.left() + delta.x());
        }
        if (m_edge == MEdge::Right) {
            newGeometry.setRight(newGeometry.right() + delta.x());
        }
        if (m_edge == MEdge::BottomRight) {
            newGeometry.setBottomRight(newGeometry.bottomRight() + delta);
        }
        if (m_edge == MEdge::BottomLeft) {
            newGeometry.setBottomLeft(newGeometry.bottomLeft() + delta);
        }
        if (m_edge == MEdge::TopLeft) {
            newGeometry.setTopLeft(newGeometry.topLeft() + delta);
        }
        if (m_edge == MEdge::TopRight) {
            newGeometry.setTopRight(newGeometry.topRight() + delta);
        }
        setGeometry(newGeometry);
        m_dragStartPosition = event->globalPos();
    } else {
        // 更新光标形状
        MEdge edge = calculateEdge(event->pos());
        updateCursor(edge);
    }
    QWidget::mouseMoveEvent(event);
}

void MediaPlayer::mouseReleaseEvent(QMouseEvent *event) {
    m_isDragging = false;
    m_edge = MEdge::None;

    QWidget::mouseReleaseEvent(event);
}

void MediaPlayer::enterEvent(QEvent *event) {
    w->controlWidget->show();
    QMainWindow::enterEvent(event);
}

void MediaPlayer::leaveEvent(QEvent *event) {
    w->controlWidget->hide();
    QMainWindow::leaveEvent(event);
}

void MediaPlayer::updateCursor(MEdge const &edges) {
    if (edges == MEdge::TopLeft || edges == MEdge::BottomRight) {
        setCursor(Qt::SizeFDiagCursor);
    } else if (edges == MEdge::TopRight || edges == MEdge::BottomLeft) {
        setCursor(Qt::SizeBDiagCursor);
    } else if (edges == MEdge::Left || edges == MEdge::Right) {
        qDebug() << "horizontal";
        setCursor(Qt::SizeHorCursor);
    } else if (edges == MEdge::Top || edges == MEdge::Bottom) {
        setCursor(Qt::SizeVerCursor);
    } else {
        unsetCursor();
    }
}
