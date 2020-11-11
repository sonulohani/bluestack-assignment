#ifndef COMBOVIEW_H
#define COMBOVIEW_H

#include <QListView>

class ComboView : public QListView
{
public:
    ComboView(QWidget *parent = nullptr) : QListView(parent)
    {
        setStyleSheet("QListView{background-color: rgba(0,0,0,0.5);border: 2px solid "
                      "white;}QListView::item{color: #ffffff;}");
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedWidth(120);

        QFont font{this->font()};
        font.setPointSize(8);
        setFont(font);
    }
};

#endif // COMBOVIEW_H
