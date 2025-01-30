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
        sliderLayout->setContentsMargins(0, 0, 0, 0);
        //添加开始时间label
        timeLabel = new QLabel("", sliderWidget);
        timeLabel->setStyleSheet("color: white;");
        sliderLayout->addWidget(timeLabel);

        slider = new Slider(Qt::Horizontal, sliderWidget);
        slider->setStyleSheet(R"");
        sliderWidget->setLayout(sliderLayout);
    }
}
