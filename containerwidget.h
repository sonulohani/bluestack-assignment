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
    virtual ~ContainerWidget() = default;

protected:
    void timerEvent(QTimerEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    SlidingStackedWidget *m_pSlidingStackedWidget;
    QPushButton *m_pDownloadBluestackButton;
    QLabel *m_pHeaderLabel, *m_pContentLabel;
};

#endif // CONTAINERWIDGET_H
