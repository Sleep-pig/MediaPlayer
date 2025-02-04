#include "Slider.hpp"
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
    : QSlider(orientation, parent) {}

void Slider::setRange(int min, int max) {
    one_percent = (max - min) / 100;
    QSlider::setRange(min, max);
}
