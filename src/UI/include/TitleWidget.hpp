#pragma once
#include <ClickedLabel.hpp>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QWidget>

class TitleWidget : public QWidget {
    Q_OBJECT
public:
    TitleWidget(QWidget *parent = nullptr);
    ~TitleWidget() = default;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
    // void mouseDoubleClickEvent(QMouseEvent *event) override;
    // void paintEvent(QPaintEvent *event) override;


    QPushButton *getSelectedButton() {
        return slectedButton;
    };

    QLabel *getTitle() {
        return title;
    };

    ClickedLabel *getCloseLb() {
        return closeLb;
    };

    ClickedLabel *getMaximizeLb() {
        return maximizeLb;
    };

    ClickedLabel *getMinimizeLb() {
        return minimizeLb;
    };

private:
    QPushButton *slectedButton{nullptr};
    QLabel *title{nullptr};
    ClickedLabel *minimizeLb{nullptr};
    ClickedLabel *maximizeLb{nullptr};
    ClickedLabel *closeLb{nullptr};
};
