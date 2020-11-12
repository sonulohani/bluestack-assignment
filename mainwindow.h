#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ContainerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() = default;

private:
    ContainerWidget *m_pContainerWidget;
};
#endif // MAINWINDOW_H
