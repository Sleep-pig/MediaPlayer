#pragma once

#include "ShowWidget.hpp"
#include <QWidget>
#include "ControlWidget.hpp"

class MediaDialog : public QWidget {
    Q_OBJECT
    friend class ShowWidget;

public slots:
    //void onFullScreenRequest();

private:
    ControlWidget *controlWidget{nullptr};
    ShowWidget *showWidget{nullptr};

public:
    MediaDialog(QWidget *parent = nullptr);
    ~MediaDialog() = default;

    // void showVideo(QString const &path) {
    //     controlWidget->showVideo(path);
    // }
};
