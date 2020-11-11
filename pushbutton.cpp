#include "pushbutton.h"

#include <QEvent>
#include <QFontMetrics>
#include <QStyleOptionButton>
#include <QStylePainter>

PushButton::PushButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    setMouseTracking(true);
    QFont font{this->font()};
    font.setPointSize(12);

    setFont(font);

    QFontMetrics fontMetrics{this->font()};
    textBoundingRect = fontMetrics.boundingRect(text);
    setFixedSize(textBoundingRect.width(), 40);

    installEventFilter(this);
}

bool PushButton::eventFilter(QObject *obj, QEvent *event)
{
    if (qobject_cast<PushButton *>(obj) == this) {
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

void PushButton::paintEvent(QPaintEvent *)
{
    QString tempText;
    QStylePainter p{this};
    QStyleOptionButton opt;
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
    p.restore();
}
