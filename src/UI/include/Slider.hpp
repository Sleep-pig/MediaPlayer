#pragma once
#include <qobjectdefs.h>
#include <QSlider>

class Slider : public QSlider {
    Q_OBJECT

private:
    bool isPress{false};
    int lastLocation{0};
    int one_percent{0};
signals:
    void sliderClicked();
    void sliderMoved(int value);
    void sliderReleased();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    Slider(Qt::Orientation orientation, QWidget *parent = nullptr);
    void setRange(int min, int max);

    bool getIsPress() const {
        return this->isPress;
    }
};
