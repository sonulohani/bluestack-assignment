#include "imageviewlabel.h"

#include <chrono>
#include <QDebug>
#include <QDir>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPushButton>
#include <QResizeEvent>

constexpr QPointF ImageViewLabel::PIXMAP_POS;

ImageViewLabel::ImageViewLabel(const QString &imagePath, QWidget *parent) : QLabel(parent)
{
    setScaledContents(true);
    auto pixmap{drawPixmap(imagePath)};
    this->setPixmap(pixmap);
}

QPixmap ImageViewLabel::drawPixmap(const QString &imagePath)
{
    QPixmap pixmap{WIDTH + 200, HEIGHT + 200};
    pixmap.fill(Qt::transparent);

    QPainter painter{&pixmap};
    painter.drawPixmap(0, 0, WIDTH + 200, HEIGHT + 200, applyBlurToPixmap(QPixmap{imagePath}));

    painter.drawPixmap(PIXMAP_POS.x(),
                       PIXMAP_POS.y(),
                       WIDTH,
                       HEIGHT,
                       QPixmap{imagePath}.scaledToHeight(HEIGHT, Qt::SmoothTransformation));

    painter.end();

    return pixmap;
}

QPixmap ImageViewLabel::applyBlurToPixmap(const QPixmap &src)
{
    if (src.isNull())
        return QPixmap();

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    QGraphicsBlurEffect blur;
    blur.setBlurRadius(10.0);
    item.setPixmap(src);
    item.setGraphicsEffect(&blur);
    scene.addItem(&item);
    QPixmap result{src.size()};
    result.fill(Qt::transparent);
    QPainter painter{&result};
    scene.render(&painter, QRectF(), QRectF(0, 0, src.width(), src.height()));
    return result;
}

void ImageViewLabel::setNewPixmap()
{
    if (m_imageFileInfoList.empty())
        return;

    static auto fileInfoListIt{m_imageFileInfoList.begin()};
    if (fileInfoListIt == m_imageFileInfoList.end()) {
        fileInfoListIt = m_imageFileInfoList.begin();
    }

    auto pixmap{drawPixmap(fileInfoListIt->absoluteFilePath())};
    this->setPixmap(pixmap);
    ++fileInfoListIt;
}
