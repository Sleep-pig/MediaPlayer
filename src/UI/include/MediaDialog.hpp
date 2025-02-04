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

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton &&
            event->pos().y() <= controlWidget->titlebar->height()) {
            isDragging = true;
            dragPosition =
                event->globalPos() - parentWidget()->frameGeometry().topLeft();
            emit startDragging(dragPosition);
        }
        QWidget::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isDragging) {
            emit dragging(event->globalPos());
        }
        QWidget::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        isDragging = false;
        QWidget::mouseReleaseEvent(event);
    }

signals:
    void startDragging(QPoint offset);
    void dragging(QPoint position);

public:
    MediaDialog(QWidget *parent = nullptr);

    ~MediaDialog() {
        qDebug() << "MediaDialog::~MediaDialog()";
    };

    void showVideo(QString const &path) {
        controlWidget->showVideo(path);
    }
};
