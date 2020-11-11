#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H

#include <array>
#include <QWidget>

class ToolButton;
class QLabel;
class PushButton;
class ComboBox;
class QHBoxLayout;
class QSpacerItem;

class TopBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopBarWidget(QWidget *parent = nullptr);
    virtual ~TopBarWidget() = default;

private:
    ToolButton *m_pStreamingToolButton;
    ToolButton *m_pGamersToolButton;
    ToolButton *m_pAboutToolButton;
    QLabel *m_pBluestacksLogo;
    PushButton *m_pAppsButton;
    PushButton *m_pBlogButton;
    PushButton *m_pSupportButton;
    PushButton *m_pContactUsButton;
    PushButton *m_pEnterpriseButton;
    ComboBox *m_pCountriesCombobox;
    QHBoxLayout *m_pParentLayout;
    std::array<QSpacerItem *, 9> m_pFixedSpacer;
    QSpacerItem *m_pExpandingSpacer;

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
};

#endif // TOPBARWIDGET_H
