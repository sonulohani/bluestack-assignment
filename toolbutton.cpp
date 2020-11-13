#include "toolbutton.h"

#include <QDebug>
#include <QEvent>
#include <QFontMetrics>
#include <QMenu>
#include <QPropertyAnimation>
#include <QStyleOptionToolButton>
#include <QStylePainter>

ToolButton::ToolButton(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setText(text);
    setMouseTracking(true);

    QFont font{this->font()};
    font.setPointSize(12);

    setFont(font);

    QFontMetrics fontMetrics{this->font()};
    textBoundingRect = fontMetrics.boundingRect(text);
    setFixedWidth(textBoundingRect.width());
    setFixedHeight(40);

    m_pMenu = new QMenu(this);
    m_pMenu->setStyleSheet(
        "QMenu::item {padding: 2px 5px 2px 2px;color: rgb(255, 255, 255);} QMenu::item:selected "
        "{background-color: rgb(0, 85, 127);color: rgb(255, 255, 255);}"
        "QMenu{background-color: rgb(21, 34, 56);margin: 2px;}");
    setMenu(m_pMenu);
    setAutoRaise(true);
    installEventFilter(this);

    connect(m_pMenu, &QMenu::aboutToShow, [=]() {
        QPropertyAnimation *pSizeAnimation{new QPropertyAnimation{m_pMenu, "size"}};
        pSizeAnimation->setDuration(1000);
        pSizeAnimation->setStartValue(QSize(m_pMenu->sizeHint().width(), 0));
        pSizeAnimation->setEndValue(
            QSize(m_pMenu->sizeHint().width(), m_pMenu->sizeHint().height()));
        pSizeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        m_pMenu->show();
    });
}

void ToolButton::addActionToMenu(const QString &actionText)
{
    QAction *pAction{new QAction{actionText, this}};
    m_pMenu->addAction(pAction);
    m_pMenu->addSeparator();
}

bool ToolButton::eventFilter(QObject *obj, QEvent *event)
{
    if (qobject_cast<ToolButton *>(obj) == this) {
        if (event->type() == QEvent::HoverEnter) {
            m_bMouseOnTop = true;
            update();
            showMenu();
        } else if (event->type() == QEvent::HoverLeave) {
            m_bMouseOnTop = false;
        }
    }
    return false;
}

void ToolButton::paintEvent(QPaintEvent *)
{
    QString tempText;
    QStylePainter p{this};
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    tempText = opt.text;
    opt.text = QString();
    p.save();
    p.setPen(m_bMouseOnTop ? QColor(42, 157, 244) : QColor(255, 255, 255));

    p.setFont(this->font());

    p.drawText(0,
               0,
               textBoundingRect.width(),
               textBoundingRect.height(),
               Qt::AlignTop | Qt::AlignHCenter,
               tempText);

    p.drawPixmap(textBoundingRect.width() / 6,
                 20,
                 QPixmap{"://resources/white-arrow-down.png"}.scaled(30,
                                                                     30,
                                                                     Qt::IgnoreAspectRatio,
                                                                     Qt::SmoothTransformation));
    p.restore();
}
