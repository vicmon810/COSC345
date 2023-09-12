#include "Recommendation.h"
#include "connection.h"
#include <QApplication>
#include <QPushButton>
#include <QMenu>
#include <QObject>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThreadPool>
#include <QFile>
/*! \mainpage Movie and Food
 *   \section intro Introduction
 *  Key Features:
 *1: Movie Recommendation: The app will analyze the user's movie preferences, ratings, and history to suggest new movies that align with their interests. It will consider factors like genre, cast, ratings, and release year.
 *
 *2: Food Pairing Suggestions: In addition to movie recommendations, the app will suggest suitable food options that complement the user's selected movie. It will provide recipes based on the movie chosen.
 */

/*!
 *@brief: Declaration of handleItemClicked function
 *@param item : QListWidgetItem
 */
void handleItemClicked(QListWidgetItem *item)
{
    // Get the text (movie details) from the clicked item
    QString movieDetails = item->text();

    // Create a custom dialog to show the full movie details
    QDialog dialog;
    QVBoxLayout *layout = new QVBoxLayout;

    // Display the full movie details in QLabel
    QLabel *detailsLabel = new QLabel();
    detailsLabel->setText(movieDetails);
    layout->addWidget(detailsLabel);

    dialog.setLayout(layout);
    dialog.setWindowTitle("Movie Details");
    dialog.exec();
}

/*!
 *@brief Declaration of downloadImage function
 *@param imageUrl: QString represents poster resource download link
 *@return poster images
 */
QPixmap downloadImage(const QString &imageUrl)
{
    // access to web location
    QNetworkAccessManager manager;
    QNetworkRequest request(imageUrl);
    QNetworkReply *reply = manager.get(request);
    // wait image to be loaded
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    // image download success
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QPixmap pixMap;
        pixMap.loadFromData(data);
        return pixMap;
    }
    // Error handers
    return QPixmap();
}

/*!
 *@class Image download worker class
 *@brief To enable poster image display on the GUI. Will be moved to a separate cpp and h file for the beta version
 */
class ImageDownloadWorker : public QRunnable
{
public:
    ImageDownloadWorker(const QString &imageUrl, QListWidgetItem *item)
        : m_imageUrl(imageUrl), m_item(item) {}

    void run() override
    {
        QPixmap posterPixmap = downloadImage(m_imageUrl);
        if (!posterPixmap.isNull())
        {
            qDebug();
            int newWidth = 600;
            int newHeight = 400;
            QPixmap scaledPixmap = posterPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

            // Set the scaled pixmap as the icon of the item
            m_item->setIcon(QIcon(scaledPixmap));
        }
    }

private:
    QString m_imageUrl;
    QListWidgetItem *m_item;
};

/**
 * Main function to run application
 */
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QString executablePath = QCoreApplication::applicationDirPath();
    QString qssFilePath = executablePath + "/myStyles.qss";
    QFile styleFile(qssFilePath);
    styleFile.open(QFile::ReadOnly);
    QString style = QLatin1String(styleFile.readAll());
    app.setStyleSheet(style);
    // initialize QFrame
    QFrame frame;
    frame.setGeometry(QRect(300, 400, 800, 600));

    // Query data from back-end
    cosc345::Connection conn;
    conn.est_conn();
    // Get movie and food vector structs
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    // vector<cosc345::Connection::Food> food = conn.getDetailFood();

    // Initialize QList to for display data set
    QListWidget *listWidget = new QListWidget();
    QThreadPool threadPool;
    threadPool.setMaxThreadCount(QThread::idealThreadCount());
    for (const cosc345::Connection::Movies &movie : movies)
    {
        QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
                               "Genres: " + QString::fromStdString(movie.genres) + "\n" +
                               "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" +
                               "Overview: " + QString::fromStdString(movie.overview) + "\n" +
                               "Release Date: " + QString::fromStdString(movie.release_date) + "\n" +
                               "Runtime: " + QString::fromStdString(movie.runtime) + "\n" +
                               "Rating: " + QString::fromStdString(movie.rating) + "\n" + // Convert double to QString
                               "Food: Popcorn and Ice Cream\n";                           // As of now, hardcoded food is popcorn and ice cream yay!

        QListWidgetItem *item = new QListWidgetItem(movieDetails);
        item->setSizeHint(QSize(600, 400)); // Set the size of each card
        // Start a worker in the thread pool to download the image
        QString imageUrl = QString::fromStdString(movie.poster);
        ImageDownloadWorker *worker = new ImageDownloadWorker(imageUrl, item);
        threadPool.start(worker);

        listWidget->addItem(item);
    }
    // button reaction
    QObject::connect(listWidget, &QListWidget::itemClicked, handleItemClicked);
    // create layout for items
    QGridLayout *layout = new QGridLayout;
    // append item to layout
    layout->addWidget(listWidget);

    // append layout to frame
    frame.setLayout(layout);
    // Show frame
    frame.show();

    // Start the Qt event loop
    return app.exec();
}