
#include "ClickedLabel.hpp"
#include <qboxlayout.h>
#include <qchar.h>
#include <QDebug>
#include <qglobal.h>
#include <QHBoxLayout>
#include <qnamespace.h>
#include <qpixmap.h>
#include <qsize.h>
#include <TitleWidget.hpp>

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet({R"(background-color:rgb(206, 145, 145);
                           )"});
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    // 选择按钮
    slectedButton = new QPushButton("选择", this);
    slectedButton->setFixedSize(30, 30);
    slectedButton->setStyleSheet(
        "QPushButton{border:none;color:white;}"
        "QPushButton:hover{color:rgb(212, 195, 195);}"
        "QPushButton:pressed{color:rgb(113, 81, 81);}");

    // 标题
    title = new QLabel("JiePlayer", this);
    title->setAlignment(Qt::AlignmentFlag::AlignCenter);

    // 屏幕按钮
    minimizeLb = new ClickedLabel(this);
    minimizeLb->setFixedSize(30, 30);
    QPixmap min(QString(IMG_DIR) + "/min.svg");
    // min.scaled(minimizeLb->size(), Qt::KeepAspectRatio,
    //            Qt::SmoothTransformation);
    minimizeLb->setScaledContents(true);
    minimizeLb->setPixmap(min);
    minimizeLb->setToolTip("最小化");

    maximizeLb = new ClickedLabel(this);
    maximizeLb->setFixedSize(30, 30);
    QPixmap max(QString(IMG_DIR) + "/max.svg");
    // max.scaled(maximizeLb->size(), Qt::KeepAspectRatio,
    //            Qt::SmoothTransformation);
    maximizeLb->setPixmap(max);
    maximizeLb->setScaledContents(true);
    maximizeLb->setToolTip("最大化");

    closeLb = new ClickedLabel(this);
    closeLb->setFixedSize(30, 30);
    QPixmap close(QString(IMG_DIR) + "/close.svg");
    closeLb->setPixmap(close);
    closeLb->setScaledContents(true);
    closeLb->setToolTip("关闭");

    layout->addWidget(slectedButton);
    layout->addWidget(title);
    layout->addWidget(minimizeLb);
    layout->addWidget(maximizeLb);
    layout->addWidget(closeLb);

    setLayout(layout);
}
