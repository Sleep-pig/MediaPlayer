#pragma once
#include "MediaDialog.hpp"
#include <qglobal.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpoint.h>
#include <QWidget>

enum class MEdge {
    None = 0,
    Left = 1,
    Right = 2,
    Top = 4,
    Bottom = 8,
    Title = 16,
    TopLeft = Top | Left,
    TopRight = Top | Right,
    BottomLeft = Bottom | Left,
    BottomRight = Bottom | Right,
};

class MediaPlayer : public QMainWindow {
    Q_OBJECT

public:
    MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();
    MEdge calculateEdge(QPoint const &pos);
    void updateCursor(MEdge const &edges);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QPoint dragOffset;

    bool m_isDragging{false};
    QPoint m_dragStartPosition;
    QPoint m_dragPosition;
    int m_borderPixel{5};
    MEdge m_edge{MEdge::None};

private:
    MediaDialog *w{nullptr};
    bool mousePressed;
    QPoint mousePoint;
};
