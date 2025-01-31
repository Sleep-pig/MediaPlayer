#include "Slider.hpp"
#include <qslider.h>

Slider::Slider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent) {}

void Slider::setRange(int min, int max) {
    QSlider::setRange(min, max);
}
