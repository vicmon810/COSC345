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

    homeList = conn.getDetailMovie();
    // Calculate the initial tempResult based on maxPerPage
    auto begin = movies.begin();
    auto end = begin + maxPerPage;

    // Ensure that end doesn't exceed the vector's size
    if (end > movies.end())
    {
        end = movies.end();
    }

    tempResult = vector<cosc345::Connection::Movies>(begin, end);
}

void MainWindow::setupUI()
{
    backendInit();

    QWidget *centralWidget = new QWidget(this);

    this->setCentralWidget(centralWidget);
    // window.setMenu();

    // Create a layout for the central widget
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);

    QWidget *menuAndSearchContainer = new QWidget();

    // Create a layout for the menu bar and search bar
    menuAndSearchLayout = new QVBoxLayout(menuAndSearchContainer);

    // Create a custom widget for the search bar
    QPushButton pageNum("Page Numbers");

    // create a push button for home
    QPushButton *home = new QPushButton(this);
    QIcon homeIcon("home.png");
    home->setIcon(homeIcon);

    // Create a push button for shuffle
    QPushButton *shuffle = new QPushButton(this);
    QIcon shuffleIcon("shuffle.png");
    shuffle->setIcon(shuffleIcon);

    QWidget *searchWidget = new QWidget();
    QHBoxLayout *searchLayout = new QHBoxLayout(searchWidget);

    QWidget *buttons = new QWidget();
    buttonLayout = new QHBoxLayout(buttons);

    // Boolean check for updating page numbers
    pageCheck = false;

    // Next page of movies
    pageNum1 = new QPushButton("<< ", this);
    pageNum1->setStyleSheet("background-color: grey;");
    pageNum2 = new QPushButton("Next >>", this);
    // Search bar
    searchBar = new QLineEdit();
    searchBar->setClearButtonEnabled(true);
    QIcon searchIcon("searchIcon.png");
    searchBar->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchBar->setPlaceholderText("Search Movie name or Genres ...");

    // Add the search bar and buttons to the search widget
    searchLayout->addWidget(home);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(shuffle);

    menuAndSearchContainer->setObjectName("menuAndSearchContainer");
    searchBar->setObjectName("searchBar");

    // Create a QLabel for the title
    QLabel *titleLabel = new QLabel("MOVIE + FOOD");
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the title
    titleLabel->setObjectName("titleLabel");

    // Add the title label to the layout
    menuAndSearchLayout->addWidget(titleLabel);

    buttonLayout->addWidget(pageNum1);

    // Add the search widget to the menu and search layout
    menuAndSearchLayout->addWidget(searchWidget);
    menuAndSearchLayout->addWidget(buttons);

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
    displayPosters(movies);

    // Connect signals to slots
    connect(home, &QPushButton::clicked, this, &MainWindow::handleHome);
    connect(shuffle, &QPushButton::clicked, this, &MainWindow::handleShuffle);
    connect(searchBar, &QLineEdit::returnPressed, this, &MainWindow::handleSearch);
    connect(pageNum1, &QPushButton::clicked, this, &MainWindow::handlePageNumberPrev);
    connect(pageNum2, &QPushButton::clicked, this, &MainWindow::handlePageNumberNext);
}

void MainWindow::displayPosters(vector<cosc345::Connection::Movies> movies)
{
    isFinish = false;
    const int layoutCols = 3; // Number of columns in your layout
    int row = 0;
    int col = 0;
    // check  pages
    pages = searchResult.size() / maxPerPage;
    remain = searchResult.size() % maxPerPage;
    // if there is remain then add one more page for it
    if (remain > 0)
        pages++;
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
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Sleep for 3 seconds
    isFinish = true;
    cout << "Displaying Posters..." << endl;

    // GPT help
    pageNumberLabel = new QLabel(this);
    pageNumberLabel->setObjectName("pageNumberLabel");
    pageNumberLabel->setAlignment(Qt::AlignCenter); // Center align the page number
    pageNumberLabel->setText(QString("PAGE %1 OF %2").arg(page1).arg(pages));
    pageNumberLabel->setFixedWidth(750);
    buttonLayout->addWidget(pageNumberLabel);
    buttonLayout->addWidget(pageNum2);
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
    // Clear the page number label
    delete pageNumberLabel;
    pageNumberLabel = nullptr;
}

void MainWindow ::handleHome()
{
    if (isFinish)
    {
        searchBar->clear();
        // reset pages
        page1 = 1;
        page2 = 2;
        pageNum1->setText("<<");
        pageNum2->setText("Next >>");
        pageNum1->setStyleSheet("background-color: grey;");
        pageNum2->setStyleSheet("background-color: #4eeddb;");
        searchResult = conn.getDetailMovie();
        pages = (homeList.size() / maxPerPage) + 1;
        cout << pages << endl;

        // Calculate the initial tempResult based on maxPerPage
        auto begin = homeList.begin();
        auto end = begin + maxPerPage;
        // Ensure that end doesn't exceed the vector's size
        if (end > homeList.end())
        {
            end = homeList.end();
        }
        tempResult = vector<cosc345::Connection::Movies>(begin, end);
        clearPosters();
        displayPosters(homeList);
        if (verticalScrollBar)
        {

            verticalScrollBar->setValue(0);
        }
    }
}

void MainWindow::handleShuffle()
{
    if (isFinish)
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed);
        shuffle(searchResult.begin(), searchResult.end(), generator);
        searchBar->clear();
        // Reset page numbers
        page1 = 1;
        page2 = 2;
        pageNum1->setText("<<");
        pageNum2->setText("Next >>");
        pageNum1->setStyleSheet("background-color: grey;");
        pageNum2->setStyleSheet("background-color: #4eeddb;");
        pages = (searchResult.size() / maxPerPage) + 1;

        clearPosters();
        displayPosters(searchResult);
        if (verticalScrollBar)
        {

            verticalScrollBar->setValue(0);
        }
    }
}

void MainWindow::handleSearch()
{
    // Get the search text from the searchBar
    string newSearchText = searchBar->text().toStdString();
    transform(newSearchText.begin(), newSearchText.end(), newSearchText.begin(), ::tolower);

    if (newSearchText != defaultText)
    {
        defaultText = newSearchText;
        searchResult = conn.searching(newSearchText);

        // Check if theres 0 movies, give popup notification
        if (searchResult.size() == 0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Movie Search");
            msgBox.setText("There are no movies or genres\nthat match " + QString::fromStdString(newSearchText));
            msgBox.exec();
            // Clear search bar
            handleHome();
            return;
        }

        // reset pages
        page1 = 1;
        page2 = 2;
        pageNum1->setText("<<");
        pageNum2->setText("Next >>");
        pageNum1->setStyleSheet("background-color: grey;");
        pageNum2->setStyleSheet("background-color: #4eeddb;");

        cout << "start sorting page" << endl;
        int pages = searchResult.size() / maxPerPage;
        int remain = searchResult.size() % maxPerPage;
        clearPosters();
        displayPosters(searchResult);

        // Set the position of the vertical scrollbar to the top
        if (verticalScrollBar)
        {
            verticalScrollBar->setValue(0);
        }

        if (searchResult.size() < maxPerPage)
        {
            pageNum1->setText("<<");
            pageNum2->setText(">>");
            pageNum1->setStyleSheet("background-color: grey;");
            pageNum2->setStyleSheet("background-color: grey;");
        }
        else
        {
            pageNum1->setText("<<");
            pageNum2->setText("Next >>");
            pageNum1->setStyleSheet("background-color: grey;");
            pageNum2->setStyleSheet("background-color: #4eeddb;");
        }
    }
}

void MainWindow::handlePageNumberPrev()
{
    if (isFinish)
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
                pageNum2->setText("Next >>");
                pageNum2->setStyleSheet("background-color: #4eeddb;");
            }
            else
            {

                pageNum1->setText("<< Prev");
                pageNum1->setStyleSheet("background-color: #4eeddb;");
                pageNum2->setText("Next >>");
                pageNum2->setStyleSheet("background-color: #4eeddb;");
            }
            // Set the position of the vertical scrollbar to the top
            if (verticalScrollBar)
            {

                verticalScrollBar->setValue(0);
            }

            // update gridLayout with subset of searchResult
            if (searchResult.size() >= maxPerPage)
            {
                // Exception for page1 == 1
                if (page1 == 1)
                {
                    tempResult = vector<cosc345::Connection::Movies>(searchResult.begin(), searchResult.end());
                }
                else
                {

                    tempResult = vector<cosc345::Connection::Movies>(searchResult.begin() + ((page1 - 1) * maxPerPage) - 1, searchResult.end());

                    cout << page1 << endl;
                    cout << tempResult.size() << endl;
                }

                clearPosters();
                displayPosters(tempResult);
            }
        }
    }
}

void MainWindow::handlePageNumberNext()
{
    if (isFinish)
    {
        cout << "What" << isFinish << endl;
        if (page2 > pages || searchResult.size() < maxPerPage)
        {
            // No more pages to display or not enough items for pagination
            return;
        }

        page1++;
        pageNum1->setText(page1 == 1 ? "<<" : "<< Prev");
        pageNum1->setStyleSheet("background-color: #4eeddb;");

        page2++;

        if (page2 > pages)
        {
            pageNum2->setStyleSheet("background-color: grey;");
            pageNum2->setText("");
        }
        else
        {
            pageNum2->setText("Next >>");
        }

        // Set the position of the vertical scrollbar to the top
        if (verticalScrollBar)
        {
            verticalScrollBar->setValue(0);
        }

        // Update the displayed posters
        if (searchResult.size() >= maxPerPage)
        {
            int startIndex = (page1 - 1) * maxPerPage;
            int endIndex = std::min(startIndex + maxPerPage, static_cast<int>(searchResult.size()));
            tempResult = std::vector<cosc345::Connection::Movies>(searchResult.begin() + startIndex, searchResult.begin() + endIndex);
            clearPosters();
            displayPosters(tempResult);
        }
    }
}