#pragma once
#include "MediaDialog.hpp"
#include <qglobal.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpoint.h>
#include <QWidget>

class MediaPlayer : public QMainWindow {
    Q_OBJECT

public:
    MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();
    Qt::Edges calculateEdge(QPoint const &pos);
    bool ConfirmEdge(Qt::Edges &edge);
    void updateCursor(Qt::Edges &edges);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:

    void handleStartDragging(QPoint offset) {
        dragOffset = offset;
    }

    void handleDragging(QPoint position) {
        move(position - dragOffset);
    }

private:
    QPoint dragOffset;

    bool m_isDragging{false};
    QPoint m_dragStartPosition;
    int m_borderWidth{3};
    Qt::Edges m_dragEdge = Qt::Edges();

private:
    MediaDialog *w{nullptr};
    bool mousePressed;
    QPoint mousePoint;
};
