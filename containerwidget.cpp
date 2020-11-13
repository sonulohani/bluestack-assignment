#include "containerwidget.h"
#include "imageviewlabel.h"
#include "slidingstackedwidget.h"
#include "topbarwidget.h"

#include <chrono>
#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QScreen>
#include <QTransform>

ContainerWidget::ContainerWidget(QWidget *parent) : QWidget(parent)
{
    auto imageFileInfoList = [] {
        const QStringList &filters{"*.png", "*.jpg", "*.bmp"};
        return QDir{"images"}.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
    }();
    if (!imageFileInfoList.isEmpty()) {
        imageFileInfoList.append(imageFileInfoList.first());
    }

    new TopBarWidget{this};

    m_pSlidingStackedWidget = new SlidingStackedWidget{this};

    for (const auto &imageFileInfo : imageFileInfoList) {
        m_pSlidingStackedWidget->addWidget(
            new ImageViewLabel{imageFileInfo.absoluteFilePath(), this});
    }

    auto *layout = new QHBoxLayout{this};
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_pSlidingStackedWidget);

    setLayout(layout);

    startTimer(std::chrono::seconds(3));

    m_pHeaderLabel = new QLabel{this};
    m_pHeaderLabel->setText(QObject::tr("BlueStacks Editor's Choice"));
    m_pHeaderLabel->setStyleSheet("QLabel {color: #89CCDF;}");
    m_pHeaderLabel->setFixedSize(320, 30);
    QFont font{m_pHeaderLabel->font()};
    font.setPointSize(16);
    font.setBold(false);
    m_pHeaderLabel->setFont(font);

    m_pContentLabel = new QLabel{this};
    m_pContentLabel->setText(QObject::tr(
        "Every week we pick our favourite android apps that look and play beautifully on your PC"));
    m_pContentLabel->setStyleSheet("QLabel {color: #FFFFFF;}");
    font = m_pContentLabel->font();
    font.setPointSize(11);
    m_pContentLabel->setFont(font);
    m_pContentLabel->setFixedSize(1000, 30);

    m_pDownloadBluestackButton = new QPushButton{this};
    m_pDownloadBluestackButton->setText(QObject::tr("Download BlueStacks"));
    m_pDownloadBluestackButton->setFixedSize(275, 60);
    m_pDownloadBluestackButton->setStyleSheet(
        "QPushButton{background-color: #89CCE7; color: white;border: none;font-size: "
        "13pt;border-radius: 10px;}");
    m_pDownloadBluestackButton->show();
    m_pDownloadBluestackButton->raise();
}

void ContainerWidget::timerEvent(QTimerEvent *)
{
    m_pSlidingStackedWidget->slideInNext();
}

void ContainerWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_pSlidingStackedWidget->count()) {
        auto pImageViewLabel = qobject_cast<ImageViewLabel *>(
            m_pSlidingStackedWidget->currentWidget());
        if (pImageViewLabel) {
            auto pCenterImageLabel = pImageViewLabel->getCenterLabel();
            auto centerImageLabelframeGeometry = pCenterImageLabel->frameGeometry();
            m_pDownloadBluestackButton->move(ImageViewLabel::PIXMAP_POS.x()
                                                 + centerImageLabelframeGeometry.width()
                                                 - m_pDownloadBluestackButton->width(),
                                             ImageViewLabel::PIXMAP_POS.y()
                                                 - m_pDownloadBluestackButton->height() - 16);

            m_pHeaderLabel->move(ImageViewLabel::PIXMAP_POS.x(),
                                 ImageViewLabel::PIXMAP_POS.y() - 85);
            m_pContentLabel->move(ImageViewLabel::PIXMAP_POS.x(),
                                  ImageViewLabel::PIXMAP_POS.y() - 50);
        }
    }
}
