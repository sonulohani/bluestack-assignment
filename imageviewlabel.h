#ifndef IMAGEVIEWLABEL_H
#define IMAGEVIEWLABEL_H

#include <QFileInfoList>
#include <QLabel>
#include <QPointF>
#include <QWidget>

class ImageViewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageViewLabel(const QString &imagePath, QWidget *parent = nullptr);
    virtual ~ImageViewLabel() = default;

    QPixmap drawPixmap(const QString &imagePath);
    static QPixmap applyBlurToPixmap(const QPixmap &src);

private:
    void setNewPixmap();

private:
    static const int WIDTH = 1366;
    static const int HEIGHT = 760;

public:
    static constexpr QPointF PIXMAP_POS{100, 180};

    QFileInfoList m_imageFileInfoList;
};

#endif // IMAGEVIEWLABEL_H
