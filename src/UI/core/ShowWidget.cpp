#include "ShowWidget.hpp"
#include <ffmpeg5.1.6/libavutil/hwcontext.h>
#include <qdebug.h>
#include <qglobal.h>
#include <QVBoxLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    backgroundWidget = new QWidget(this);
    backgroundWidget->setStyleSheet("background-color: black;");
    layout->addWidget(backgroundWidget);
}

void ShowWidget::onInitVideoOutput(int format) {
    if (backgroundWidget) {
        this->layout()->removeWidget(backgroundWidget);
        delete backgroundWidget;
        backgroundWidget = nullptr;
    }

    if (curGLWidgetFormat == format) {
        return;
    }

    curGLWidgetFormat = format;

    if (glWidget) {
        delete glWidget;
    }

    if (format == AV_HWDEVICE_TYPE_NONE) {
        qDebug() << "YUV420P_WIDGET";
        // glWidget = new YUV420PWidget(this);
        // this->layout()->addWidget(glWidget);
    } else {
        qDebug() << "NV12GL_WIDGET";
        // glWidget = new Nv12GLWidget(this);
        // this->layout()->addWidget(glWidget);
    }
}

void ShowWidget::recvFrame(uint8_t *pixeldata, int pixelwidth,
                           int pixelHeight) {
    if (glWidget) {
        //todo  setPixelData
    }
}
