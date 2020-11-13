#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QEasingCurve>
#include <QStackedWidget>
#include <QWidget>

class SlidingStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit SlidingStackedWidget(QWidget *parent = nullptr);

    void slideInNext();

protected slots:
    void animationDoneSlot(void);

private:
    void slideInWgt(QWidget *widget);

private:
    int m_now{};
    int m_next{};
    QPoint m_nowPt{};
    bool m_bActive{};
};

#endif // SLIDINGSTACKEDWIDGET_H
