// #include "Recommendation.h"
// #include "connection.h"
// #include <QApplication>
// #include <QPushButton>
// #include <QMenu>
// #include <QObject>
// #include <QFrame>
// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include <QCheckBox>
// #include <QLineEdit>
// #include <QTableWidget>
// #include <QTableWidgetItem>
// #include <iostream>
// #include <QDebug>
// #include <QListWidget>
// #include <QMessageBox>
// #include <QDialog>
// #include <QIcon>
// #include <QLabel>
// #include <QNetworkAccessManager>
// #include <QNetworkRequest>
// #include <QNetworkReply>
// #include <QThreadPool>
// #include <QFile>

// // Declaration of the downloadImage function
// QPixmap downloadImage(const QString &imageUrl);

// /*!
//  * \brief handleItemClicked function to display movie details
//  * \param item QListWidgetItem
//  */
// void handleItemClicked(QListWidgetItem *item)
// {
//     // Get the text (movie details) from the clicked item
//     QString movieDetails = item->text();

//     // Create a custom dialog to show the full movie details
//     QDialog dialog;
//     QVBoxLayout *layout = new QVBoxLayout;

//     // Display the full movie details in QLabel
//     QLabel *detailsLabel = new QLabel();
//     detailsLabel->setText(movieDetails);
//     layout->addWidget(detailsLabel);

//     dialog.setLayout(layout);
//     dialog.setWindowTitle("Movie Details");
//     dialog.exec();
// }

// /*!
//  * \brief The ImageDownloadWorker class to download and display poster images
//  */
// class ImageDownloadWorker : public QRunnable
// {
// public:
//     ImageDownloadWorker(const QString &imageUrl, QListWidgetItem *item)
//         : m_imageUrl(imageUrl), m_item(item) {}

//     void run() override
//     {
//         QPixmap posterPixmap = downloadImage(m_imageUrl);
//         if (!posterPixmap.isNull())
//         {
//             int newWidth = 600;
//             int newHeight = 400;
//             QPixmap scaledPixmap = posterPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

//             // Set the scaled pixmap as the icon of the item
//             m_item->setIcon(QIcon(scaledPixmap));
//         }
//     }

// private:
//     QString m_imageUrl;
//     QListWidgetItem *m_item;
// };

// /*!
//  * \brief The downloadImage function to download an image from a URL
//  * \param imageUrl QString represents poster resource download link
//  * \return poster images
//  */
// QPixmap downloadImage(const QString &imageUrl)
// {
//     // Access web location
//     QNetworkAccessManager manager;
//     QNetworkRequest request(imageUrl);
//     QNetworkReply *reply = manager.get(request);

//     // Wait for the image to be loaded
//     QEventLoop loop;
//     QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//     loop.exec();

//     // Check if image download was successful
//     if (reply->error() == QNetworkReply::NoError)
//     {
//         QByteArray data = reply->readAll();
//         QPixmap pixMap;
//         pixMap.loadFromData(data);
//         return pixMap;
//     }

//     // Error handler
//     return QPixmap();
// }

// /**
//  * \brief Main function to run the application
//  */
// int main(int argc, char **argv)
// {
//     QApplication app(argc, argv);
//     QString executablePath = QCoreApplication::applicationDirPath();
//     QString qssFilePath = executablePath + "/myStyles.qss";
//     QFile styleFile(qssFilePath);
//     styleFile.open(QFile::ReadOnly);
//     QString style = QLatin1String(styleFile.readAll());
//     app.setStyleSheet(style);

//     // Initialize QFrame
//     QFrame frame;
//     frame.setGeometry(QRect(300, 400, 800, 600));

//     // Query data from the back-end
//     cosc345::Connection conn;
//     conn.est_conn();

//     // Get movie and food vector structs
//     std::vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();

//     // Initialize QListWidget to display the data set
//     QListWidget *listWidget = new QListWidget();
//     QThreadPool threadPool;
//     threadPool.setMaxThreadCount(QThread::idealThreadCount());

//     for (const cosc345::Connection::Movies &movie : movies)
//     {
//         QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
//                                "Genres: " + QString::fromStdString(movie.genres) + "\n" +
//                                "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" +
//                                "Overview: " + QString::fromStdString(movie.overview) + "\n" +
//                                "Release Date: " + QString::fromStdString(movie.release_date) + "\n" +
//                                "Runtime: " + QString::fromStdString(movie.runtime) + "\n" +
//                                "Rating: " + QString::fromStdString(movie.rating) + "\n" +
//                                "Food: Popcorn and Ice Cream\n";

//         QListWidgetItem *item = new QListWidgetItem(movieDetails);
//         item->setSizeHint(QSize(600, 400)); // Set the size of each card

//         // Start a worker in the thread pool to download the image
//         QString imageUrl = QString::fromStdString(movie.poster);
//         ImageDownloadWorker *worker = new ImageDownloadWorker(imageUrl, item);
//         threadPool.start(worker);

//         listWidget->addItem(item);
//     }

//     // Connect itemClicked signal to handleItemClicked slot
//     QObject::connect(listWidget, &QListWidget::itemClicked, handleItemClicked);

//     // Create layout for items
//     QGridLayout *layout = new QGridLayout;
//     // Append items to layout
//     layout->addWidget(listWidget);

//     // Append layout to frame
//     frame.setLayout(layout);

//     // Show the frame
//     frame.show();

//     // Start the Qt event loop
//     return app.exec();
// }
