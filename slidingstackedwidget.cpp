#include "slidingstackedwidget.h"
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    if (parent != nullptr) {
        m_mainwindow = parent;
    } else {
        m_mainwindow = this;
    }

    m_vertical = false;
    m_speed = 500;
    m_animationtype = QEasingCurve::OutBack;
    m_now = 0;
    m_next = 0;
    m_wrap = false;
    m_pnow = QPoint(0, 0);
    m_active = false;
}

void SlidingStackedWidget::setVerticalMode(bool vertical)
{
    m_vertical = vertical;
}

void SlidingStackedWidget::setSpeed(int speed)
{
    m_speed = speed;
}

void SlidingStackedWidget::setAnimation(enum QEasingCurve::Type animationtype)
{
    m_animationtype = animationtype;
}

void SlidingStackedWidget::setWrap(bool wrap)
{
    m_wrap = wrap;
}

void SlidingStackedWidget::slideInNext()
{
    if (m_next == count() - 1) {
        setCurrentIndex(0);
        m_next = 0;
        m_now = 0;
    }

    int now = currentIndex();

    if (m_wrap || (now < count() - 1)) {
        slideInIdx(now + 1);
        if (now == count()) {
            setCurrentIndex(0);
        }
    }
}

void SlidingStackedWidget::slideInIdx(int idx, enum t_direction direction)
{
    //int idx, t_direction direction=AUTOMATIC
    if (idx > count() - 1) {
        direction = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
        idx = (idx) % count();
    } else if (idx < 0) {
        direction = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
        idx = (idx + count()) % count();
    }
    slideInWgt(widget(idx), direction);
}

void SlidingStackedWidget::slideInWgt(QWidget *newwidget, enum t_direction direction)
{
    if (m_active) {
        return;
    } else {
        m_active = true;
    }
    enum t_direction directionhint;
    int now = currentIndex();
    int next = indexOf(newwidget);
    if (now == next) {
        m_active = false;
        return;
    } else if (now < next) {
        directionhint = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
    } else {
        directionhint = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
    }
    if (direction == AUTOMATIC) {
        direction = directionhint;
    }

    int offsetx = frameRect().width();
    int offsety = frameRect().height();

    widget(next)->setGeometry(0, 0, offsetx, offsety);
    if (direction == BOTTOM2TOP) {
        offsetx = 0;
        offsety = -offsety;
    } else if (direction == TOP2BOTTOM) {
        offsetx = 0;
    } else if (direction == RIGHT2LEFT) {
        offsetx = -offsetx;
        offsety = 0;
    } else if (direction == LEFT2RIGHT) {
        offsety = 0;
    }

    QPoint pnext = widget(next)->pos();
    QPoint pnow = widget(now)->pos();
    m_pnow = pnow;
    widget(next)->move(pnext.x() - offsetx, pnext.y() - offsety);

    widget(next)->show();
    widget(next)->raise();

    QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
    animnext->setDuration(m_speed);
    animnext->setEasingCurve(m_animationtype);
    animnext->setStartValue(QPoint(-offsetx + pnext.x(), offsety + pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));
    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(animnext);
    QObject::connect(animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
    m_next = next;
    m_now = now;
    m_active = true;
    animgroup->start();
}

void SlidingStackedWidget::animationDoneSlot(void)
{
    setCurrentIndex(m_next);
    widget(m_now)->hide();
    widget(m_now)->move(m_pnow);
    m_active = false;
    emit animationFinished();
}
