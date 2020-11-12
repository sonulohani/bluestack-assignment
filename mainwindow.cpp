#include "mainwindow.h"
#include "containerwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QObject::tr("Bluestacks"));

    m_pContainerWidget = new ContainerWidget{this};
    setCentralWidget(m_pContainerWidget);
}
