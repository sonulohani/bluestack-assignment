#ifndef COMBOVIEW_H
#define COMBOVIEW_H

#include <QListView>

class ComboView : public QListView
{
    Q_OBJECT
public:
    explicit ComboView(QWidget *parent = nullptr) : QListView(parent)
    {
        setStyleSheet("QListView{background-color: rgba(0,0,0,0.5);border: 2px solid "
                      "white;}QListView::item{color: #ffffff;padding-bottom: 5px;}");
        setFixedWidth(140);

        QFont font{this->font()};
        font.setPointSize(12);
        setFont(font);
    }

    virtual ~ComboView() = default;
};

#endif // COMBOVIEW_H
