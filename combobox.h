#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QWidget>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent = nullptr);
    virtual ~ComboBox() = default;

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // COMBOBOX_H
