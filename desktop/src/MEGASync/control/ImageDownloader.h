#ifndef IMAGE_DOWNLOADER_H
#define IMAGE_DOWNLOADER_H

#include <QImage>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include <memory>

struct ImageData
{
    QString url = QString();
    QImage::Format format;

    ImageData(const QString& url, QImage::Format format = QImage::Format_ARGB32_Premultiplied):
        url(url),
        format(format)
    {
    }
};

class ImageDownloader : public QObject
{
    Q_OBJECT

public:
    enum class Error
    {
        NoError = 0,
        NetworkError,
        InvalidUrl,
        EmptyData,
        InvalidImage
    };

    explicit ImageDownloader(QObject* parent = nullptr);
    explicit ImageDownloader(unsigned int timeout, QObject* parent = nullptr);
    virtual ~ImageDownloader() = default;

public slots:
    void downloadImage(const QString& imageUrl,
                       QImage::Format format = QImage::Format_ARGB32_Premultiplied);

signals:
    void downloadFinished(const QImage& image,
                          const QString& imageUrl);
    void downloadFinishedWithError(const QString& imageUrl,
                                   Error error,
                                   QNetworkReply::NetworkError networkError = QNetworkReply::NoError);

private slots:
    void onRequestImgFinished(QNetworkReply* reply);

private:
    QMap<QNetworkReply*, std::shared_ptr<ImageData>> mReplies;
    std::unique_ptr<QNetworkAccessManager> mManager;
    unsigned int mTimeout;

    bool validateReply(QNetworkReply* reply, const QString& url, QByteArray& bytes);
    void processImageData(const QByteArray& bytes, const std::shared_ptr<ImageData>& imageData);

};

#endif // IMAGE_DOWNLOADER_H

