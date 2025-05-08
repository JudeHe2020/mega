#include "ApiImageLabel.h"

#include "Utilities.h"

#include <QPainter>

namespace
{
constexpr int DownloadTimeout = 5000;
const QLatin1String IMAGE_NAME_PREFIX(".");
const QLatin1String HIGH_RESOLUTION_SUFFIX("@2x");
const QLatin1String HIGH_RESOLUTION_SUFFIX_REGEXP("@2x$");
const int MINIMUM_PIXEL_RATIO(2);
const int IMAGE_FILENAME_INDEX(0);
}

ApiImageLabel::ApiImageLabel(QWidget* parent):
    QLabel(parent),
    mDownloader(std::make_unique<ImageDownloader>(DownloadTimeout))
{
    connect(mDownloader.get(),
            &ImageDownloader::downloadFinished,
            this,
            &ApiImageLabel::onDownloadFinished);
    connect(mDownloader.get(),
            &ImageDownloader::downloadFinishedWithError,
            this,
            &ApiImageLabel::onDownloadError);
}

void ApiImageLabel::setImageUrl(QString url)
{
    if (Utilities::getDevicePixelRatio() >= MINIMUM_PIXEL_RATIO)
    {
        QString imageName =
            QFileInfo(url).fileName().split(IMAGE_NAME_PREFIX).at(IMAGE_FILENAME_INDEX);
        if (!imageName.contains(QRegExp(HIGH_RESOLUTION_SUFFIX_REGEXP)))
        {
            url.replace(imageName, imageName + HIGH_RESOLUTION_SUFFIX);
        }
    }

    mDownloader->downloadImage(url);
}

void ApiImageLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if (!mImage.isNull())
    {
        if (mImage.size().width() < size().width() && mImage.size().height() < size().height())
        {
            QRect labelRect(QPoint(0, 0), size());
            QRect imageRect(mImage.rect());
            imageRect.moveCenter(labelRect.center());

            painter.drawImage(imageRect, mImage, mImage.rect());
        }
        else
        {
            painter.drawImage(QRect(QPoint(0, 0), size()), mImage, mImage.rect());
        }
    }
}

void ApiImageLabel::onDownloadFinished(const QImage& image, const QString&)
{
    mImage = image;
    emit imageReady(true);
}

void ApiImageLabel::onDownloadError(const QString&,
                                    ImageDownloader::Error,
                                    QNetworkReply::NetworkError)
{
    mImage = QImage();
    emit imageReady(false);
}

const QImage& ApiImageLabel::image() const
{
    return mImage;
}
