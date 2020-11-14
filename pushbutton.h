#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    PushButton(const QString &text, QWidget *parent = nullptr);
    virtual ~PushButton() = default;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    QRectF textBoundingRect;
    bool m_bMouseOnTop{false};
    QCursor m_defaultCursor;
};

#endif // PUSHBUTTON_H
