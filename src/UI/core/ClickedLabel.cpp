#include <ClickedLabel.hpp>
#include <qlabel.h>
ClickedLabel::ClickedLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent,f) {}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QLabel::mouseReleaseEvent(event);
}
