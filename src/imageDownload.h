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
    class ImageDownloadWorker : public QRunnable
    {
    public:
        ImageDownloadWorker(const QString &imageUrl, QLabel *imageLabel);
        QPixmap downloadImage(const QString &imageUrl);
        void run() override;

    private:
        QString m_imageUrl;
        QLabel *m_imageLabel;
    };
}
#endif // IMAGEDOWNLOADWORKER_H
