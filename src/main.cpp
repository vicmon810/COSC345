#include "Recommendation.h"
#include "connection.h"
#include "clickImage.h"
#include "clickHandler.h"
#include <algorithm>
#include <random>

/*! \mainpage Movie and Food
 *   \section intro Introduction
 *  Key Features:
 *1: Movie Recommendation: The app will analyze the user's movie preferences, ratings, and history to suggest new movies that align with their interests. It will consider factors like genre, cast, ratings, and release year.
 *
 *2: Food Pairing Suggestions: In addition to movie recommendations, the app will suggest suitable food options that complement the user's selected movie. It will provide recipes based on the movie chosen.
 */

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

vector<cosc345::Connection::Movies> getAllMovie()
{
    cosc345::Connection conn;
    conn.est_conn();
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    return movies;
}

int getAllSize()
{
    cosc345::Connection conn;
    conn.est_conn();
    return conn.getSizeMovie();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Load QSS style sheet
    QString executablePath = QCoreApplication::applicationDirPath();
    QString qssFilePath = executablePath + "/myStyles.qss";
    QFile styleFile(qssFilePath);
    styleFile.open(QFile::ReadOnly);
    QString style = QLatin1String(styleFile.readAll());
    app.setStyleSheet(style);

    // Back-end work, query data
    vector<cosc345::Connection::Movies> movies = getAllMovie();
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
    //QAction *openAction = fileMenu->addAction("search");

    // Create a QWidgetAction to add a custom widget to the menu
    QWidgetAction* searchWidgetAction = new QWidgetAction(&window);

    // Create a custom widget for the search bar
    QWidget* searchWidget = new QWidget();
    QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);

    QLineEdit *searchBar = new QLineEdit();
    searchBar->setClearButtonEnabled(true);
    QIcon searchIcon("searchIcon.png");
    // Add the action with the loaded icon
    searchBar->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchBar->setPlaceholderText("Search...");

    // Add the search bar to the search widget
    searchLayout->addWidget(searchBar);

    // Set the custom widget as the default widget for the action
    searchWidgetAction->setDefaultWidget(searchWidget);

    // Add the search action to the File menu
    fileMenu->addAction(searchWidgetAction);
    
    
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
    // return all movies size
    // int size = getAllSize();
    int size = 500;
    // Create and add 7800 items to the grid layout
    const int numCols = 3;             // Number of rows
    const int numRows = size / 20; // Number of columns             CHANGE THIS FOR LIMITED LOAD TIMES

    int i = 0;
    for (int row = 0; row < numRows; ++row)
    {

        for (int col = 0; col < numCols; ++col)
        {
            // ClickableLabel imageLabel = new ClickableLabel();

            QString name = QString::fromStdString(movies[i].title);
            QString genres = QString::fromStdString(movies[i].genres);
            QString IMDB = QString::fromStdString(movies[i].imdb_id);
            QString overview = QString::fromStdString(movies[i].overview);
            QString runtime = QString::fromStdString(movies[i].runtime);
            QString rating = QString::fromStdString(movies[i].rating);
            QString release = QString::fromStdString(movies[i].release_date);
            QString URL = QString::fromStdString(movies[i].poster);

            // Create a QLabel to display the image
            // QLabel *imageLabel = new QLabel();
            ClickableLabel *imageLabel = new ClickableLabel();

            QObject::connect(imageLabel, &ClickableLabel::clicked, [=]()
                             {
                                 // Code to execute when the label is clicked
                                 cosc345::clickHandler ch;
                                 ch.handleItemClicked(name, genres, IMDB, overview, runtime, rating, release);
                                 // qDebug()
                                 //     << "Label clicked!";
                             });
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