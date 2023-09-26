#include "Recommendation.h"
#include "connection.h"
#include "clickImage.h"
#include "clickHandler.h"

#include "PagingStyle.h"
#include <algorithm>
#include <random>
#include <map>

using namespace cosc345;
using namespace std;

// Declare the imageMap as a global variable
map<QString, QPixmap> imageMap;

/*! \mainpage Movie and Food
 *   \section intro Introduction
 *  Key Features:
 *1: Movie Recommendation: The app will analyze the user's movie preferences, ratings, and history to suggest new movies that align with their interests. It will consider factors like genre, cast, ratings, and release year.
 *
 *2: Food Pairing Suggestions: In addition to movie recommendations, the app will suggest suitable food options that complement the user's selected movie. It will provide recipes based on the movie chosen.
 */

// typedef QMap<QString, QPixmap> posterMap;

/**
 *  Function to download an image synchronously
 */
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

/**
 *  Image download worker class
 */
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

/**
 * Function to display movie posters on GUI
 */
void displayPoster(vector<cosc345::Connection::Movies> movies, QGridLayout *gridLayout, Recommendation rec)
{
    if (imageMap.empty())
    {
        cout << "not empty!!" << endl;
    }
    // Create and add 7800 items to the grid layout
    int size = movies.size();
    if (size > 50)
        size = 50;
    cout << size << endl;
    const int numCols = 3;              // Number of rows
    const int numRows = size / numCols; // Number of columns             CHANGE THIS FOR LIMITED LOAD TIMES

    int i = 0;

    cout << "Acquiring movie posters...." << endl;

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            // ClickableLabel imageLabel = new ClickableLabel();
            // cout << i << endl;
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
                                 ch.handleItemClicked(name, genres, IMDB, overview, runtime, rating, release, rec);
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

    cout << "Movie posters acquired!...." << endl;
}

/**
 * MAIN FUNCTION
 */
int main(int argc, char **argv)
{
    string searchText = "";
    int searchFigure = 0;

    QApplication app(argc, argv);

    // Load QSS style sheet
    QString executablePath = QCoreApplication::applicationDirPath();
    QString qssFilePath = executablePath + "/myStyles.qss";
    QFile styleFile(qssFilePath);
    if (!styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed to open QSS file: " << styleFile.errorString();
        return -1;
    }
    QString style = QLatin1String(styleFile.readAll());
    styleFile.close();

    // Set the application's style sheet
    app.setStyleSheet(style);

    // Back-end work, query data
    cosc345::Connection conn;
    conn.est_conn();

    //Original movies vector
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    // Create searchResult movies
    vector<cosc345::Connection::Movies> searchResult = movies;

    // Test food query
    vector<cosc345::Connection::Food> foods = conn.getDetailFood();

    // Create Recommendation class instance
    Recommendation rec = Recommendation(movies, foods);

    QMainWindow window;
    window.setWindowTitle("Movie and Food");
    // Create a central widget for the main window
    QWidget *centralWidget = new QWidget();
    window.setCentralWidget(centralWidget);
    // window.setMenu();

    // Create a layout for the central widget
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);

    // Create a custom QWidget to hold both the menu bar and the search bar
    QWidget *menuAndSearchContainer = new QWidget();

    // Create a layout for the menu bar and search bar
    QVBoxLayout *menuAndSearchLayout = new QVBoxLayout(menuAndSearchContainer);

    // Create a custom widget for the search bar
    QPushButton pageNum("Page Numbers");
    QWidget *searchWidget = new QWidget();
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);

    // Variables for page number 
    int page1 = 1;
    int page2 = 2;

    // Boolean check for updating page numbers
    bool pageCheck = false;

    //Next page of movies
    QPushButton pageNum1("<< 1");
    QPushButton pageNum2("2 >>");

    QLineEdit *searchBar = new QLineEdit();
    searchBar->setClearButtonEnabled(true);
    QIcon searchIcon("searchIcon.png");
    searchBar->addAction(searchIcon, QLineEdit::LeadingPosition);

    searchBar->setPlaceholderText("Search...");

    // Add the search bar and buttons to the search widget 
    searchLayout->addWidget(&pageNum1);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(&pageNum2);

    // Add the search widget to the menu and search layout
    menuAndSearchLayout->addWidget(searchWidget);

    // Set the custom QWidget as the menu bar for the main window
    window.setMenuWidget(menuAndSearchContainer);

    // Create a scroll area
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setMinimumSize(1000, 1000);
    scrollArea->setWidgetResizable(true);
    centralWidget->setLayout(new QVBoxLayout());
    centralWidget->layout()->addWidget(scrollArea);

    // Create a widget to hold the grid layout
    QWidget *scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);

    QGridLayout *gridLayout = new QGridLayout(scrollWidget);

    // Auto runs displayPoster when app is launched to give grid layout of movie posters
    displayPoster(movies, gridLayout, rec);

    // Connect the returnPressed() signal of QLineEdit to a slot
        // For input to searchbar
    QObject::connect(searchBar, &QLineEdit::returnPressed, [&]()
        {
            //To reset page numbers
            pageCheck = true;
            searchText = searchBar->text().toStdString();
            transform(searchText.begin(), searchText.end(), searchText.begin(), ::tolower);
            // Print the contents to the console
            // std::cout << "Search Text: " << searchText << std::endl;

            searchResult = conn.searching(searchText);
            cout << searchResult.size() << endl;
            searchFigure = searchResult.size();

            int resultSize = searchResult.size();

            QLayoutItem* item;
            while ((item = gridLayout->takeAt(0)) != nullptr)
            {
                delete item->widget(); // Remove widget from layout
                delete item;// Delete layout item
            }
            displayPoster(searchResult, gridLayout, rec);

            //Update button texts if needed
            if (pageCheck) {
                page1 = 1;
                page2 = 2;
                pageNum1.setText("<< " + QString::number(page1));
                pageNum2.setText(QString::number(page2) + " >>");
                pageCheck = false;
            }

            gridLayout->update(); // update main window poster with search results
        });

    //connect for the buttons
    QObject::connect(&pageNum1, &QPushButton::clicked, [&]()
        {
            if (page1 == 1) { 
                //do nothing
            } 
            else {
                //Update button text
                page1--;
                page2--;
                pageNum1.setText("<< " + QString::number(page1));
                pageNum2.setText(QString::number(page2) + " >>");

                //update gridLayout with subset of searchResult
                vector<cosc345::Connection::Movies> tempResult(searchResult.begin() + (page1 * 50) - 1, searchResult.end());
                displayPoster(tempResult, gridLayout, rec);
                gridLayout->update();
            }
        });

    QObject::connect(&pageNum2, &QPushButton::clicked, [&]()
        {
            if (page2 == (searchResult.size() / 50)) {
                //do nothing
            }
            else {
                page1++;
                page2++;
                pageNum1.setText("<< " + QString::number(page1));
                pageNum2.setText(QString::number(page2) + " >>");

                //update gridLayout with subset of searchResult
                vector<cosc345::Connection::Movies> tempResult(searchResult.begin() + (page1 * 50) - 1, searchResult.end());
                displayPoster(tempResult, gridLayout, rec);
                gridLayout->update();
            }
        });

    window.setLayout(gridLayout);

    // Show the main window
    window.show();
    return app.exec();
}
