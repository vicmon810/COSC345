#include "imageDownload.h"

// Image download worker class
class ImageDownloadWorker : public QRunnable
{
public:
    QPixmap downloadImage(const QString &imageUrl)
    {
        QNetworkAccessManager manager;
        QNetworkRequest request(imageUrl);
        QNetworkReply *reply = manager.get(request);

        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(data);
            return pixmap;
        }
        else
        {
            qDebug() << "Failed to download image:" << reply->errorString();
            return QPixmap(); // Return an empty pixmap in case of an error
        }
    }

    ImageDownloadWorker(const QString &imageUrl, QLabel *imageLabel)
        : m_imageUrl(imageUrl), m_imageLabel(imageLabel) {}

    void run() override
    {
        QPixmap posterPixmap = downloadImage(m_imageUrl);
        if (!posterPixmap.isNull())
        {
            // Set the downloaded image as the pixmap of the QLabel
            m_imageLabel->setPixmap(posterPixmap);
        }
    }

private:
    QString m_imageUrl;
    QLabel *m_imageLabel;
};