#include "MainWindow.h"

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
        QPixmap defaultImage("no-image-icon.png");
        return defaultImage; // Return an empty pixmap in case of an error
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
        // qDebug() << posterPixmap.size();
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    verticalScrollBar = nullptr;
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::backendInit()
{
    // Back-end work, query data
    conn.est_conn();

    // Original movies vector
    movies = conn.getDetailMovie(); // Assign to the class member variable
    // Create searchResult movies
    searchResult = movies;
    // Test food query
    foods = conn.getDetailFood(); // Assign to the class member variable

    rec = Recommendation(movies, foods);
}

void MainWindow::setupUI()
{
    backendInit();

    QWidget *centralWidget = new QWidget(this);

    this->setCentralWidget(centralWidget);
    // window.setMenu();

    // Create a layout for the central widget
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);

    // Create a checkbox
    // QCheckBox *action = new QCheckBox("Action", this);

    // QCheckBox
    //     checkBox->setChecked(false); // Default: unchecked

    // // Create a label to display the checkbox state
    // QLabel *label = new QLabel("Feature is disabled", this);

    // Connect the checkbox stateChanged signal to a slot
    // QObject::connect(checkBox, &QCheckBox::stateChanged, [&label](int state));

    // Add the checkbox and label to the central layout
    // centralLayout->addWidget(checkBox);
    // centralLayout->addWidget(label);
    // Create a custom QWidget to hold both the menu bar and the search bar
    QWidget *menuAndSearchContainer = new QWidget();

    // Create a layout for the menu bar and search bar
    QVBoxLayout *menuAndSearchLayout = new QVBoxLayout(menuAndSearchContainer);

    // Create a custom widget for the search bar
    QPushButton pageNum("Page Numbers");
    QWidget *searchWidget = new QWidget();
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);

    // Boolean check for updating page numbers
    pageCheck = false;

    // Next page of movies
    pageNum1 = new QPushButton("<< ", this);
    pageNum1->setStyleSheet("background-color: grey;");
    pageNum2 = new QPushButton("Next >>", this);

    searchBar = new QLineEdit();
    searchBar->setClearButtonEnabled(true);
    QIcon searchIcon("searchIcon.png");
    searchBar->addAction(searchIcon, QLineEdit::LeadingPosition);

    searchBar->setPlaceholderText("Search Movie name or Genres ...");

    // Add the search bar and buttons to the search widget
    searchLayout->addWidget(pageNum1);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(pageNum2);

    menuAndSearchContainer->setObjectName("menuAndSearchContainer");
    searchBar->setObjectName("searchBar");

    // Create a QLabel for the title
    QLabel *titleLabel = new QLabel("MOVIE + FOOD");
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the title
    titleLabel->setObjectName("titleLabel");

    // Add the title label to the layout
    menuAndSearchLayout->addWidget(titleLabel);

    // Add the search widget to the menu and search layout
    menuAndSearchLayout->addWidget(searchWidget);

    // Set the custom QWidget as the menu bar for the main window
    this->setMenuWidget(menuAndSearchContainer);

    // Create a scroll area
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setMinimumSize(1000, 1000);
    scrollArea->setWidgetResizable(true);
    centralWidget->setLayout(new QVBoxLayout());
    centralWidget->layout()->addWidget(scrollArea);

    // Create a widget to hold the grid layout
    QWidget *scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);
    // Get the vertical scrollbar of the QScrollArea
    verticalScrollBar = scrollArea->verticalScrollBar();
    gridLayout = new QGridLayout(scrollWidget);
    // Auto runs displayPoster when app is launched to give grid layout of movie posters
    displayPosters(movies, gridLayout, rec);

    // Connect signals to slots
    connect(searchBar, &QLineEdit::returnPressed, this, &MainWindow::handleSearch);
    connect(pageNum1, &QPushButton::clicked, this, &MainWindow::handlePageNumberPrev);
    connect(pageNum2, &QPushButton::clicked, this, &MainWindow::handlePageNumberNext);
}

void MainWindow::displayPosters(vector<cosc345::Connection::Movies> movies, QGridLayout *gridLayout, Recommendation rec)
{
    // clearPosters(gridLayout);
    // int maxPerPage = 51;
    const int layoutCols = 3; // Number of columns in your layout

    // int pages = movies.size() / maxPerPage;

    int row = 0;
    int col = 0;

    for (const auto &movie : movies)
    {

        QString name = QString::fromStdString(movie.title);
        QString genres = QString::fromStdString(movie.genres);
        QString IMDB = QString::fromStdString(movie.imdb_id);
        QString overview = QString::fromStdString(movie.overview);
        QString runtime = QString::fromStdString(movie.runtime);
        QString rating = QString::fromStdString(movie.rating);
        QString release = QString::fromStdString(movie.release_date);
        QString URL = QString::fromStdString(movie.poster);

        // Create a QLabel to display the image
        QPixmap presetImage("no-image-icon.png");
        ClickableLabel *imageLabel = new ClickableLabel();
        imageLabel->setPixmap(presetImage);

        QObject::connect(imageLabel, &ClickableLabel::clicked, [=]()
                         {
                             // Code to execute when the label is clicked
                             cosc345::clickHandler ch;
                             ch.handleItemClicked(name, genres, IMDB, overview, runtime, rating, release, rec); });

        gridLayout->addWidget(imageLabel, row, col);
        // Create an ImageDownloadWorker to download and display the image
        ImageDownloadWorker *imageWorker = new ImageDownloadWorker(URL, imageLabel);

        QThreadPool::globalInstance()->start(imageWorker);

        // Update the column and row for the next poster
        col++;
        if (col >= layoutCols)
        {
            col = 0;
            row++;
        }

        // If you've displayed the maximum number of posters, you can break the loop
        if (row * layoutCols + col >= maxPerPage)
        {
            break;
        }
    }

    cout << "Displaying Posters..." << endl;
}

void MainWindow::clearPosters()
{
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();
        if (widget)
        {
            gridLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }
}

void MainWindow::handleSearch()
{

    // Get the search text from the searchBar
    string newSearchText = searchBar->text().toStdString();
    transform(newSearchText.begin(), newSearchText.end(), newSearchText.begin(), ::tolower);
    if (newSearchText == defaultText)
    {
        // do nothing;
    }
    else
    {

        defaultText = newSearchText;
        searchResult = conn.searching(newSearchText);
        int pages = searchResult.size() / maxPerPage;
        int remain = searchResult.size() % maxPerPage;
        clearPosters();
        displayPosters(searchResult, gridLayout, rec);
        // Set the position of the vertical scrollbar to the top
        if (verticalScrollBar)
        {

            verticalScrollBar->setValue(0);
        }
    }
}

void MainWindow::handlePageNumberPrev()
{
    if (page1 == 1)
    {
        // do nothing
    }
    else
    {
        // Update button text
        page1--;
        page2--;

        if (page1 == 1)
        {
            pageNum1->setText("<<");
            pageNum1->setStyleSheet("background-color: grey;");
            // pageNum1->setStyleSheet()
            pageNum2->setText("Next >>");
        }
        else
        {

            pageNum1->setText("<< Prev");
            pageNum1->setStyleSheet("background-color: #4eeddb;");
            pageNum2->setText("Next >>");
        }
        // Set the position of the vertical scrollbar to the top
        if (verticalScrollBar)
        {

            verticalScrollBar->setValue(0);
        }

        // update gridLayout with subset of searchResult
        if (searchResult.size() >= maxPerPage)
        {
            vector<cosc345::Connection::Movies> tempResult;

            // Exception for page1 == 1
            if (page1 == 1)
            {
                tempResult = vector<cosc345::Connection::Movies>(searchResult.begin(), searchResult.end());
            }
            else
            {

                tempResult = vector<cosc345::Connection::Movies>(searchResult.begin() + (page1 * maxPerPage) - 1, searchResult.end());
            }

            clearPosters();
            displayPosters(tempResult, gridLayout, rec);
        }
    }
}

void MainWindow::handlePageNumberNext()
{
    // check  pages
    int pages = searchResult.size() / maxPerPage;
    int remain = searchResult.size() % maxPerPage;

    // if there is remain then add one more page for it
    if (remain > 0)
        pages++;

    if (page2 > pages || searchResult.size() < maxPerPage)
    {
        // do nothing
        // cout << page2 << endl;
        // cout << (searchResult.size() / maxPerPage) << endl;
    }
    else
    {

        page1++;
        if (page1 != 1)
        {
            pageNum1->setText("<< Prev");
            pageNum1->setStyleSheet("background-color: #4eeddb;");
        }
        page2++;
        if (page2 == pages)
        {
            pageNum1->setText("<< Pev");
            pageNum2->setText("");
        }
        pageNum1->setText("<< Prev");
        pageNum2->setText("Next >>");
        // Set the position of the vertical scrollbar to the top
        if (verticalScrollBar)
        {
            verticalScrollBar->setValue(0);
        }
        // update gridLayout with subset of searchResult
        if (searchResult.size() >= maxPerPage)
        {
            vector<cosc345::Connection::Movies> tempResult(searchResult.begin() + (page1 * maxPerPage) - 1, searchResult.end());

            clearPosters();
            displayPosters(tempResult, gridLayout, rec);
        }
    }
}
