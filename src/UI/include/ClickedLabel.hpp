#pragma once
#include <QLabel>
#include <QMouseEvent>
#include <qobjectdefs.h>
#include <QWidget>

class ClickedLabel : public QLabel {
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void clicked();
};
