#include "combobox.h"
#include "comboview.h"

#include <QFont>
#include <QListView>
#include <QStylePainter>

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    setView(new ComboView);
    setStyleSheet("QComboBox::drop-down {border: 0px; } QComboBox { background: rgba( 255, 255, "
                  "255, 0% ); border: 2px solid white; "
                  "border-radius: 5px;} QComboBox::down-arrow "
                  "{ image: url(://resources/white-arrow-down.png);width: 40px;height: "
                  "40px;margin-right:10px;}");
}

void ComboBox::paintEvent(QPaintEvent *)
{
    QStylePainter painter{this};
    painter.setPen(palette().color(QPalette::Text));

    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    opt.currentText = "";
    opt.frame = true;
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    if (currentIndex() < 0)
        opt.palette.setBrush(QPalette::ButtonText,
                             opt.palette.brush(QPalette::ButtonText).color().lighter());

    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}
