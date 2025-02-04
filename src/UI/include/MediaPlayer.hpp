#pragma once
#include "MediaDialog.hpp"
#include <qglobal.h>
#include <qmainwindow.h>
#include <qobjectdefs.h>
#include <qpoint.h>
#include <QWidget>

class MediaPlayer : public QMainWindow {
    Q_OBJECT

public:
    MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();

    // protected:
    //     bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleStartDragging(QPoint offset) {
        dragOffset = offset;
    }

    void handleDragging(QPoint position) {
        move(position - dragOffset);
    }

private:
    QPoint dragOffset;

private:
    MediaDialog *w{nullptr};
    bool mousePressed;
    QPoint mousePoint;
};
