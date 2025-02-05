#include "MediaPlayer.hpp"
#include "MediaDialog.hpp"
#include <QFileDialog>
#include <qglobal.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <QPushButton>
#include <QStandardPaths>
#include <qwidget.h>

MediaPlayer::MediaPlayer(QWidget *parent) : QMainWindow(parent) {
    setAttribute(Qt::WA_Hover);
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
            &MediaPlayer::handleStartDragging, Qt::DirectConnection);
    connect(w, &MediaDialog::dragging, this, &MediaPlayer::handleDragging,
            Qt::DirectConnection);
}

MediaPlayer::~MediaPlayer() {}

Qt::Edges MediaPlayer::calculateEdge(QPoint const &pos) {
    Qt::Edges edges;
    int x = pos.x();
    int y = pos.y();
    int w = width();
    int h = height();

    if (x < m_borderWidth) {
        edges |= Qt::LeftEdge;
    }
    if (x > w - m_borderWidth) {
        edges |= Qt::RightEdge;
    }
    if (y < m_borderWidth) {
        edges |= Qt::TopEdge;
    }
    if (y > h - m_borderWidth) {
        edges |= Qt::BottomEdge;
    }

    if (x < m_borderWidth && y < m_borderWidth) {
        edges |= Qt::LeftEdge | Qt::TopEdge;
    }
    if (x > w - m_borderWidth && y < m_borderWidth) {
        edges |= Qt::RightEdge | Qt::TopEdge;
    }
    if (x < m_borderWidth && y > h - m_borderWidth) {
        edges |= Qt::LeftEdge | Qt::BottomEdge;
    }
    if (x > w - m_borderWidth && y > h - m_borderWidth) {
        edges |= Qt::RightEdge | Qt::BottomEdge;
    }
    return edges;
}

bool MediaPlayer::ConfirmEdge(Qt::Edges &edge) {
    if (edge == Qt::LeftEdge || edge == Qt::RightEdge || edge == Qt::TopEdge ||
        edge == Qt::BottomEdge || (edge == Qt::LeftEdge | Qt::TopEdge) ||
        (edge == Qt::RightEdge | Qt::TopEdge) ||
        (edge == Qt::LeftEdge | Qt::BottomEdge) ||
        (edge == Qt::RightEdge | Qt::BottomEdge)) {
        return true;
    }
    return false;
}

void MediaPlayer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->globalPos();
        m_dragEdge = calculateEdge(m_dragStartPosition);
        m_isDragging = ConfirmEdge(m_dragEdge);
    }
    QWidget::mousePressEvent(event);
}

void MediaPlayer::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging) {
        // 拖拽调整窗口大小
        QPoint delta = event->globalPos() - m_dragStartPosition;
        QRect newGeometry = geometry();

        if (m_dragEdge & Qt::LeftEdge) {
            newGeometry.setLeft(newGeometry.left() + delta.x());
        }
        if (m_dragEdge & Qt::RightEdge) {
            newGeometry.setRight(newGeometry.right() + delta.x());
        }
        if (m_dragEdge & Qt::TopEdge) {
            newGeometry.setTop(newGeometry.top() + delta.y());
        }
        if (m_dragEdge & Qt::BottomEdge) {
            newGeometry.setBottom(newGeometry.bottom() + delta.y());
        }

        setGeometry(newGeometry);
        m_dragStartPosition = event->globalPos();
    } else {
        // 更新光标形状
        Qt::Edges edge = calculateEdge(event->pos());
        updateCursor(edge);
    }
    QWidget::mouseMoveEvent(event);
}

void MediaPlayer::mouseReleaseEvent(QMouseEvent *event) {
    m_isDragging = false;
    m_dragEdge = Qt::Edges();
    QWidget::mouseReleaseEvent(event);
}

void MediaPlayer::updateCursor(Qt::Edges& edges) {
    if (edges == (Qt::LeftEdge | Qt::TopEdge) || edges == (Qt::RightEdge | Qt::BottomEdge)) {
        setCursor(Qt::SizeFDiagCursor);
    } else if (edges == (Qt::RightEdge | Qt::TopEdge) || edges == (Qt::LeftEdge | Qt::BottomEdge)) {
        setCursor(Qt::SizeBDiagCursor);
    } else if (edges & (Qt::LeftEdge | Qt::RightEdge)) {
        setCursor(Qt::SizeHorCursor);
    } else if (edges & (Qt::TopEdge | Qt::BottomEdge)) {
        setCursor(Qt::SizeVerCursor);
    } else {
        unsetCursor();
    }
}
