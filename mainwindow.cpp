#include "mainwindow.h"
#include "containerwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QObject::tr("Bluestacks"));

    containerWidget = new ContainerWidget{this};
    setCentralWidget(containerWidget);
}
