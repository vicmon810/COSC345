#include "Recommendation.h"
#include "connection.h"
#include "clickImage.h"
#include <algorithm>
#include <random>
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
#include <QMainWindow>
#include <QScrollArea>
#include <QFile>
#include <QPixmap>
#include <QMenuBar>
// #include "myStyles.qss"
/*! \mainpage Movie and Food
 *   \section intro Introduction
 *  Key Features:
 *1: Movie Recommendation: The app will analyze the user's movie preferences, ratings, and history to suggest new movies that align with their interests. It will consider factors like genre, cast, ratings, and release year.
 *
 *2: Food Pairing Suggestions: In addition to movie recommendations, the app will suggest suitable food options that complement the user's selected movie. It will provide recipes based on the movie chosen.
 */

QString
getMovieDetial()
{
    // Query data from back-end
    cosc345::Connection conn;
    conn.est_conn();
    // Get movie and food vector structs
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    // vector<cosc345::Connection::Food> food = conn.getDetailFood();

    for (const cosc345::Connection::Movies &movie : movies)
    {
        QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
                               "Genres: " + QString::fromStdString(movie.genres) + "\n" +
                               "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" +
                               "Overview: " + QString::fromStdString(movie.overview) + "\n" +
                               "Release Date: " + QString::fromStdString(movie.release_date) + "\n" +
                               "Runtime: " + QString::fromStdString(movie.runtime) + "\n" +
                               "Rating: " + QString::fromStdString(movie.rating) + "\n" + // Convert double to QString
                               "Food: Monster Drink\n";                                   // As of now, hardcoded food is popcorn and ice cream yay!
                                                                                          // QString movieTitle = "Title: " + QString::fromStdString(movie.title);

        return movieDetails;
        // Start a worker in the thread pool to download the image
    }
}

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

// Function to download an image synchronously
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

// Image download worker class
class ImageDownloadWorker : public QRunnable
{
public:
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

int main(int argc, char **argv)
{
    string searchText = "";

    QApplication app(argc, argv);

    // Load QSS style sheet
    QString executablePath = QCoreApplication::applicationDirPath();
    QString qssFilePath = executablePath + "/myStyles.qss";
    QFile styleFile(qssFilePath);
    styleFile.open(QFile::ReadOnly);
    QString style = QLatin1String(styleFile.readAll());
    app.setStyleSheet(style);

    // initialize QFrame
    // QFrame frame;
    // frame.setGeometry(QRect(300, 400, 800, 600));

    // Back-end work, query data
    cosc345::Connection conn;
    conn.est_conn();
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    shuffle(movies.begin(), movies.end(), default_random_engine());
    QMainWindow window;
    window.setWindowTitle("Movie and Food");
    // Create a central widget for the main window
    QWidget *centralWidget = new QWidget();
    window.setCentralWidget(centralWidget);
    // window.setMenu();

    // Create a menu bar
    QMenuBar *menuBar = new QMenuBar(&window);

    // Set the menu bar for the main window
    window.setMenuBar(menuBar);

    // Create a File menu
    QMenu *fileMenu = menuBar->addMenu("File");
    // Create a QAction for the File menu
    QAction *openAction = fileMenu->addAction("search");

    // Create a scroll area
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setMinimumSize(1000, 1000);
    scrollArea->setWidgetResizable(true);
    centralWidget->setLayout(new QVBoxLayout());
    centralWidget->layout()->addWidget(scrollArea);

    // Create a widget to hold the grid layout
    QWidget *scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);

    // Create a grid layout
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);

    // Create and add 7800 items to the grid layout
    const int numCols = 3;                       // Number of rows
    const int numRows = conn.getSizeMovie() / 3; // Number of columns
    int i = 0;
    for (int row = 0; row < numRows; ++row)
    {

        for (int col = 0; col < numCols; ++col)
        {
            // ClickableLabel imageLabel = new ClickableLabel();

            QString name = QString::fromStdString(movies[i].title);
            QString Genres = QString::fromStdString(movies[i].genres);
            QString IMDB = QString::fromStdString(movies[i].imdb_id);
            // QString Overview = QString::
            QString URL = QString::fromStdString(movies[i].poster);

            // Create a QLabel to display the image
            // QLabel *imageLabel = new QLabel();
            ClickableLabel *imageLabel = new ClickableLabel();
            QObject::connect(imageLabel, &ClickableLabel::clicked, [=]()
                             {
    // Code to execute when the label is clicked
    qDebug() << "Label clicked!"; });
            // imageLabel->setFixedSize(128, 192);
            gridLayout->addWidget(imageLabel, row, col);
            // imageLabel->resize(128, 192);
            // Create a QPushButton for the title
            QPushButton *titleButton = new QPushButton((name));
            // gridLayout->addWidget(titleButton, row, col);

            // Create an ImageDownloadWorker to download and display the image
            ImageDownloadWorker *imageWorker = new ImageDownloadWorker(URL, imageLabel);
            QThreadPool::globalInstance()->start(imageWorker);

            i++;
        }
    }
    QHBoxLayout *layout = new QHBoxLayout;

    window.setLayout(gridLayout);
    // Show the main window
    window.show();

    return app.exec();
}