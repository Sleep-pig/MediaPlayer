#include "MediaPlayer.hpp"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[]) {
// 在linux中要添加这一段代码，否则无法拖动无边框窗口
#ifdef Q_OS_LINUX
    qputenv("QT_QPA_PLATFORM", "xcb");
#endif
    QApplication a(argc, argv);

    MediaPlayer w;
    w.show();
    return a.exec();
}
