#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QRectF>
#include <QToolButton>
#include <QWidget>

class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    ToolButton(const QString &text, QWidget *parent = nullptr);
    virtual ~ToolButton() = default;

    void addActionToMenu(const QString &actionText);

protected:
    void paintEvent(QPaintEvent *) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QRectF textBoundingRect;
    QMenu *m_pMenu;
    bool m_bMouseOnTop{false};
};

#endif // TOOLBUTTON_H
