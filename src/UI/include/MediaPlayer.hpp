#pragma once
#include <QWidget>

class MediaPlayer : public QWidget {
    Q_OBJECT
private:
public:
    MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();
};
