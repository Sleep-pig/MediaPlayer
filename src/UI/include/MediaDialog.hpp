#pragma once

#include "ControlWidget.hpp"
#include "ShowWidget.hpp"
#include <qglobal.h>
#include <qpoint.h>
#include <qwidget.h>
#include <QWidget>

class MediaDialog : public QWidget {
    Q_OBJECT
    friend class ShowWidget;
    friend class MediaPlayer;

public slots:

    // void onFullScreenRequest();

private:
    ControlWidget *controlWidget{nullptr};
    ShowWidget *showWidget{nullptr};
    bool isDragging;
    QPoint dragPosition;


public:
    MediaDialog(QWidget *parent = nullptr);

    ~MediaDialog() {
        qDebug() << "MediaDialog::~MediaDialog()";
    };

    void showVideo(QString const &path) {
        controlWidget->showVideo(path);
    }
};
