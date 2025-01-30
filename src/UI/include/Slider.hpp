#pragma once
#include <qobjectdefs.h>
#include <QSlider>

class Slider : public QSlider {
    Q_OBJECT
signals:
    void sliderClicked();
    void sliderMoved(int value);
    void sliderReleased();
public:
    Slider(Qt::Orientation orientation, QWidget *parent = nullptr);
    void setRange(int min, int max);

};
