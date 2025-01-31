#include "MediaPlayer.hpp"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    MediaPlayer w;
    w.show();
    return a.exec();
}
