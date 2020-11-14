#include "topbarwidget.h"
#include "combobox.h"
#include "comboview.h"
#include "pushbutton.h"
#include "toolbutton.h"

#include <QDebug>
#include <QDomDocument>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPair>
#include <QResizeEvent>
#include <QSpacerItem>
#include <QVector>

namespace {
auto retrievElements(QDomElement root, QString tag, QString att) -> QVector<QPair<QString, QString>>
{
    QDomNodeList nodes{root.elementsByTagName(tag)};
    QVector<QPair<QString, QString>> countryCodeWithNameVec;

    for (int i = 0; i < nodes.count(); i++) {
        QDomNode elm{nodes.at(i)};
        if (elm.isElement()) {
            QDomElement e{elm.toElement()};
            countryCodeWithNameVec.push_back(
                QPair<QString, QString>{e.attribute(att), e.firstChild().toText().data()});
        }
    }

    return countryCodeWithNameVec;
}

void showMessageBox(const QString &msg)
{
    QMessageBox msgBox;
    msgBox.setText("");
    msgBox.setStyleSheet(
        "QLabel{min-width: "
        + QString::number(QFontMetrics(msgBox.font()).boundingRect(msg).width() + 20) + "px;}");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
}

TopBarWidget::TopBarWidget(QWidget *parent) : QWidget(parent)
{
    if (parent) {
        parent->installEventFilter(this);
        raise();
    }
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Window);

    QPalette pal;
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 160));
    setPalette(pal);

    m_pParentLayout = new QHBoxLayout{this};
    m_pParentLayout->setSpacing(0);
    m_pParentLayout->setMargin(0);
    m_pParentLayout->setContentsMargins(0, 0, 0, 0);

    m_pBluestacksLogo = new QLabel{this};
    auto logo_pixmap = QPixmap{"://resources/officialLogo.png"}.scaled(220,
                                                                       66,
                                                                       Qt::IgnoreAspectRatio,
                                                                       Qt::SmoothTransformation);
    m_pBluestacksLogo->setPixmap(logo_pixmap);
    m_pParentLayout->addWidget(m_pBluestacksLogo);

    m_pFixedSpacer[0] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[0]);

    m_pAppsButton = new PushButton{"Apps", this};
    m_pParentLayout->addWidget(m_pAppsButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[1] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[1]);

    m_pStreamingToolButton = new ToolButton{QObject::tr("Streaming"), this};
    m_pStreamingToolButton->addActionToMenu(QObject::tr("WHAT IS BTV?"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("STREAM FOR BLUESTACKS"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("GET INVOLVED WITH STREAMING"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("HOW TO SIGN UP"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("FILTERS"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("STREAMING DOS AND DON'T"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("BUILDING AN AUDIENCE"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("BE AWESOME"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("MAKING FRIENDS"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("HAVING TROUBLE?"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("EVERYONE LOVES GIFTS"));
    m_pStreamingToolButton->addActionToMenu(QObject::tr("RUN A TOURNAMENT"));

    m_pParentLayout->addWidget(m_pStreamingToolButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[2] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[2]);

    m_pGamersToolButton = new ToolButton{QObject::tr("Gamers"), this};
    m_pGamersToolButton->addActionToMenu(QObject::tr("GAME TESTER COMMUNITY"));
    m_pGamersToolButton->addActionToMenu(QObject::tr("SUBMIT YOUR CLASH ROYALE DECK"));

    m_pParentLayout->addWidget(m_pGamersToolButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[3] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[3]);

    m_pAboutToolButton = new ToolButton{QObject::tr("About"), this};
    m_pAboutToolButton->addActionToMenu(QObject::tr("ABOUT US"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("APP PLAYER"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("UPDATE NOTES"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("FEATURES"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("INVESTORS"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("PRESS"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("CAREERS"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("PARTNERS"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("PRESS KIT"));
    m_pAboutToolButton->addActionToMenu(QObject::tr("TEAM"));

    m_pParentLayout->addWidget(m_pAboutToolButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[4] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[4]);

    m_pBlogButton = new PushButton{QObject::tr("Blog"), this};
    m_pParentLayout->addWidget(m_pBlogButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[5] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[5]);

    m_pSupportButton = new PushButton{QObject::tr("Support"), this};
    m_pParentLayout->addWidget(m_pSupportButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[6] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[6]);

    m_pContactUsButton = new PushButton{QObject::tr("Contact Us"), this};
    m_pParentLayout->addWidget(m_pContactUsButton, 0, Qt::AlignHCenter);

    m_pFixedSpacer[7] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[7]);

    m_pEnterpriseButton = new PushButton{QObject::tr("Enterprise"), this};
    m_pParentLayout->addWidget(m_pEnterpriseButton, 0, Qt::AlignHCenter);

    m_pExpandingSpacer = new QSpacerItem{40, 0, QSizePolicy::Expanding};
    m_pParentLayout->addItem(m_pExpandingSpacer);

    m_pCountriesCombobox = new ComboBox{this};

    QDomDocument document;
    bool bCanReadXML = true;

    QFile file{"://XML/countries.xml"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file for reading.";
        bCanReadXML = false;
    } else {
        // loading
        if (!document.setContent(&file)) {
            qDebug() << "Failed to load the file for reading.";
            bCanReadXML = false;
        }
        file.close();
    }

    if (bCanReadXML) {
        QDomElement root{document.firstChildElement()};
        auto countryCodes{retrievElements(root, "country", "code")};
        for (auto code : countryCodes) {
            QPixmap pix{"://Countries/" + code.first.toLower() + ".png"};
            pix = pix.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            m_pCountriesCombobox->addItem(QIcon{pix}, code.second);
        }
    }

    m_pCountriesCombobox->setCurrentText("English");

    auto *pView = static_cast<ComboView *>(m_pCountriesCombobox->view());
    pView->setFixedHeight(pView->model()->rowCount() * 38);

    m_pCountriesCombobox->setFixedSize(80, 45);
    m_pParentLayout->addWidget(m_pCountriesCombobox, 0, Qt::AlignHCenter);

    m_pFixedSpacer[8] = new QSpacerItem{40, 0};
    m_pParentLayout->addItem(m_pFixedSpacer[8]);

    setLayout(m_pParentLayout);

    connect(m_pAppsButton, &QPushButton::clicked, [] {
        showMessageBox(QObject::tr("We have a lot of apps supported!"));
    });

    connect(m_pBlogButton, &QPushButton::clicked, [] {
        showMessageBox(QObject::tr("You can discover tons of information in our blogs."));
    });

    connect(m_pSupportButton, &QPushButton::clicked, [] {
        showMessageBox(QObject::tr("We are here to help you. Just SHOOT"));
    });

    connect(m_pContactUsButton, &QPushButton::clicked, [] {
        showMessageBox(QObject::tr("Its secret"));
    });

    connect(m_pEnterpriseButton, &QPushButton::clicked, [] {
        showMessageBox(
            QObject::tr("You seem to be a important customer. Let me present the best from us."));
    });
}

bool TopBarWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == parent()) {
        if (ev->type() == QEvent::Resize)
            resize(static_cast<QResizeEvent *>(ev)->size().width(), 90);
        else if (ev->type() == QEvent::ChildAdded)
            raise();
    }
    return QWidget::eventFilter(obj, ev);
}
