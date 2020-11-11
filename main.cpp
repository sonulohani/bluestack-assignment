#include "mainwindow.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication a{argc, argv};
    a.setWindowIcon(QIcon{"://resources/favicon.ico"});
    MainWindow w;
    w.show();
    return a.exec();
}
