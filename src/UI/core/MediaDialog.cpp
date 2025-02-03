#include "MediaDialog.hpp"
#include "ShowWidget.hpp"
#include <QStackedLayout>

MediaDialog::MediaDialog(QWidget *parent) : QWidget(parent) {
    QStackedLayout *stackedLayout = new QStackedLayout(this);
    stackedLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(stackedLayout);

    controlWidget = new ControlWidget(this);
    showWidget = new ShowWidget(this);
    stackedLayout->addWidget(showWidget);

    stackedLayout->addWidget(controlWidget);

    stackedLayout->setCurrentIndex(1);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
      connect(controlWidget->decodethPtr(), &Decode::initVideoOutput, showWidget,
            &ShowWidget::onInitVideoOutput);
    connect(controlWidget->videothPtr(), &VideoThread::SendFrame, showWidget,
            &ShowWidget::recvFrame);
}
