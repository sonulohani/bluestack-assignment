#include "slidingstackedwidget.h"
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
}

void SlidingStackedWidget::slideInNext()
{
    if (m_next == count() - 1) {
        setCurrentIndex(0);
        m_next = 0;
        m_now = 0;
    }

    int now = currentIndex();

    if (now < count() - 1) {
        slideInWgt(widget(now + 1));
    }
}

void SlidingStackedWidget::slideInWgt(QWidget *newwidget)
{
    if (m_bActive) {
        return;
    } else {
        m_bActive = true;
    }

    int now = currentIndex();
    int next = indexOf(newwidget);
    if (now == next) {
        m_bActive = false;
        return;
    }

    int offsetx = frameRect().width();
    int offsety = frameRect().height();

    widget(next)->setGeometry(0, 0, offsetx, offsety);

    offsetx = -offsetx;
    offsety = 0;

    QPoint nextPt = widget(next)->pos();
    QPoint nowPt = widget(now)->pos();
    m_nowPt = nowPt;

    widget(next)->move(nextPt.x() - offsetx, nextPt.y() - offsety);
    widget(next)->show();
    widget(next)->raise();

    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(500);
    animnext->setEasingCurve(QEasingCurve::InCubic);
    animnext->setStartValue(QPoint(-offsetx + nextPt.x(), offsety + nextPt.y()));
    animnext->setEndValue(QPoint(nextPt.x(), nextPt.y()));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(animnext);
    QObject::connect(animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));

    m_next = next;
    m_now = now;
    m_bActive = true;
    animgroup->start();
}

void SlidingStackedWidget::animationDoneSlot(void)
{
    setCurrentIndex(m_next);
    widget(m_now)->hide();
    widget(m_now)->move(m_nowPt);
    m_bActive = false;
}
