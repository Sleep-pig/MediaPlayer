#pragma once
#include <QWidget>
#include <cstdint>
#include <qobjectdefs.h>
#include <OpenGLWidget.hpp>
#include <QStackedWidget>
class ShowWidget : public QWidget {
    Q_OBJECT
public slots:
    void onInitVideoOutput(int format);
    void recvFrame(uint8_t *pixelData, int pixelWidth, int pixelHeight);

private:
    int curGLWidgetFormat{-1};
    BaseOpenGLWidget *glWidget{nullptr};
    QWidget *backgroundWidget{nullptr};
    QStackedWidget *stackedWidget{nullptr};

public:
    explicit ShowWidget(QWidget *parent = nullptr);
    ~ShowWidget() = default;
};