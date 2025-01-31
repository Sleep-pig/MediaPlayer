#include "ControlWidget.hpp"
#include <qboxlayout.h>
#include <qwidget.h>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    layout->addStretch(); // 添加弹簧 将进度条挤下面

    // 添加进度条组（包括时间 将来的声音调整 快放等）
    {
        sliderWidget = new QWidget(this);
        layout->addWidget(sliderWidget);
        QHBoxLayout *sliderLayout = new QHBoxLayout(
            sliderWidget); // 将来的其他部件就可以添加到这个水平布局中
        sliderWidget->setLayout(sliderLayout);
        sliderLayout->setContentsMargins(0, 0, 0, 0);
        // 添加开始时间label
        timeLabel = new QLabel("0", sliderWidget);
        timeLabel->setStyleSheet("color: black;");
        sliderLayout->addWidget(timeLabel);

        slider = new Slider(Qt::Horizontal, sliderWidget);
        slider->setStyleSheet({R"(
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
        slider->setValue(0);
        slider->setRange(0, 0);
        sliderLayout->addWidget(slider);

        totalTimeLabel = new QLabel("1", sliderWidget);
        totalTimeLabel->setStyleSheet("color: black;");
        sliderLayout->addWidget(totalTimeLabel);

        btn = new QPushButton("test", sliderWidget);
        btn->setStyleSheet("background-color: white;");
        sliderLayout->addWidget(btn);
    }
}

ControlWidget::~ControlWidget() {}
