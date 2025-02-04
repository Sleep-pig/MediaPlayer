#include "Slider.hpp"
#include <QDebug>
#include <qglobal.h>
#include <QMouseEvent>
#include <qslider.h>

void Slider::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isPress = true;

        double pos = event->pos().x() / (double)width();
        setValue(pos * (maximum() - minimum()) + minimum());
        emit Slider::sliderClicked();
    }
    QSlider::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() &
        Qt::LeftButton) { // button()只是返回当前按下的按钮，buttons()方法可能返回所有按下的按钮的状态。
        double pos = event->pos().x() / (double)width();
        int value = pos * (maximum() - minimum()) + minimum();
        setValue(value);
    }
    QSlider::mouseMoveEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->isPress = false;
        emit Slider::sliderMoved(this->value());
        // qDebug() << "slider_value: " << this->value();
        emit Slider::sliderReleased();
    }
    QSlider::mouseReleaseEvent(event);
}

Slider::Slider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent) {
    setStyleSheet({R"(
        background-color: transparent;

        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 5px;
            background: #c4c4c4;
            /*margin: 2px 0;*/
        }
        QSlider::handle:horizontal {
            background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #4CC2FF, stop:0.8 #5c5c5c);
            border: 2px solid #5c5c5c;
            width: 17px;
            height: 18px;
            margin: -8px 0; 
            border-radius: 10px;
        }
        QSlider::sub-page:horizontal {
            background: #4CC2FF; /* 滑块走过的部分颜色 */
        }
        QSlider::add-page:horizontal {
            background: #c4c4c4; /* 滑块未走过的部分颜色 */
        })"});
}

void Slider::setRange(int min, int max) {
    one_percent = (max - min) / 100;
    QSlider::setRange(min, max);
}
