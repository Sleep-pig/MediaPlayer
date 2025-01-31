#include "ShowWidget.hpp"
#include "MediaDialog.hpp"
#include <qdebug.h>
#include <qglobal.h>
#include <qlayoutitem.h>
#include <QVBoxLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    MediaDialog *f = dynamic_cast<MediaDialog *>(parent);
    int height = f->controlWidget->sliderWidget->height();
    QSpacerItem *lowerSpacer = new QSpacerItem(
        this->width(), height, QSizePolicy::Fixed, QSizePolicy::Minimum);
    layout->addItem(lowerSpacer);
    backgroundWidget = new QWidget(this);
    backgroundWidget->setStyleSheet("background-color: black;");
    layout->addWidget(backgroundWidget);
    QSpacerItem *upperSpacer = new QSpacerItem(
        this->width(), height, QSizePolicy::Fixed, QSizePolicy::Minimum);
    layout->addItem(upperSpacer);
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
        // todo  setPixelData
    }
}
