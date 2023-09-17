#ifndef IMAGEDOWNLOADWORKER_H
#define IMAGEDOWNLOADWORKER_H

#include <QObject>
#include <QFrame>

#include <QLineEdit>

#include <QDebug>
#include <QListWidget>
#include <QIcon>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThreadPool>
#include <QMainWindow>
#include <QScrollArea>
#include <QFile>
#include <QPixmap>
#include <QMenuBar>
#include <QLabel>
#include <QEventLoop>
namespace scosc345
{
    /*!
     * @class ImageDownloadWorker
     * @brief Represents a worker class for downloading images from URLs and displaying them on QLabel.
     *
     * This class is responsible for downloading an image from a given URL and displaying it on a QLabel.
     * It is designed to be used with QThreadPool for parallel image downloads.
     */
    class ImageDownloadWorker : public QRunnable
    {
    public:
        /*!
         * @brief Constructs an ImageDownloadWorker instance.
         * @param imageUrl The URL of the image to download.
         * @param imageLabel The QLabel where the downloaded image will be displayed.
         */
        ImageDownloadWorker(const QString &imageUrl, QLabel *imageLabel);
        /*!
         * @brief Downloads an image from the given URL.
         * @param imageUrl The URL of the image to download.
         * @return QPixmap representing the downloaded image.
         */
        QPixmap downloadImage(const QString &imageUrl);
        /*!
         * @brief The main execution function of the worker.
         *
         * This function is called when the worker is started. It downloads the image from the URL and
         * displays it on the QLabel specified during construction.
         */
        void run() override;

    private:
        QString m_imageUrl;
        QLabel *m_imageLabel;
    };
}
#endif // IMAGEDOWNLOADWORKER_H
