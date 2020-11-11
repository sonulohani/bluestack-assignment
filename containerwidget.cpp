#include "containerwidget.h"
#include "imageviewlabel.h"
#include "slidingstackedwidget.h"
#include "topbarwidget.h"

#include <chrono>
#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

ContainerWidget::ContainerWidget(QWidget *parent) : QWidget(parent)
{
    auto imageFileInfoList = [] {
        const QStringList &filters{"*.png", "*.jpg", "*.bmp"};
        return QDir{"images"}.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
    }();

    new TopBarWidget{this};

    stackedWidget = new SlidingStackedWidget{this};

    for (const auto &imageFileInfo : imageFileInfoList) {
        stackedWidget->addWidget(new ImageViewLabel{imageFileInfo.absoluteFilePath(), this});
    }

    auto *layout = new QHBoxLayout{this};
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stackedWidget);

    setLayout(layout);

    startTimer(std::chrono::seconds(3));

    header = new QLabel{this};
    header->setText("Bluestacks Editor's Choice");
    header->setStyleSheet("QLabel {color: #5EC1E9;}");
    header->setFixedSize(320, 30);
    QFont font = header->font();
    font.setPointSize(14);
    font.setBold(false);
    header->setFont(font);

    content = new QLabel{this};
    content->setText(
        "Every week we pick our favourite android apps that look and play beautifully on your PC");
    content->setStyleSheet("QLabel {color: #FFFFFF;}");
    font = content->font();
    font.setPointSize(10);
    content->setFont(font);
    content->setFixedSize(1000, 30);

    m_pDownloadBluestackButton = new QPushButton{this};
    m_pDownloadBluestackButton->setText(QObject::tr("Download Bluestacks"));
    m_pDownloadBluestackButton->setFixedSize(220, 50);
    m_pDownloadBluestackButton->setStyleSheet(
        "QPushButton{background-color: #89CDE7; color: white;border: none;font-size: "
        "11pt;font-weight: bold;}");
    m_pDownloadBluestackButton->show();
    m_pDownloadBluestackButton->raise();
}

void ContainerWidget::timerEvent(QTimerEvent *event)
{
    stackedWidget->slideInNext();
}

void ContainerWidget::resizeEvent(QResizeEvent *event)
{
    static QSize size = event->size();
    m_pDownloadBluestackButton->move(event->size().width() - 350, 110);
    header->move(ImageViewLabel::PIXMAP_POS.x(), ImageViewLabel::PIXMAP_POS.y() - 80);
    content->move(ImageViewLabel::PIXMAP_POS.x(), ImageViewLabel::PIXMAP_POS.y() - 50);
}
