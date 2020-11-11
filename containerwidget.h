#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>

class SlidingStackedWidget;
class QPushButton;
class QLabel;

class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerWidget(QWidget *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    SlidingStackedWidget *stackedWidget;
    QPushButton *m_pDownloadBluestackButton;
    QLabel *header, *content;
};

#endif // CONTAINERWIDGET_H
