// #include "MainWindow.h"

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
// {
//     setupUI();
//     displayPosters();
// }

// MainWindow::~MainWindow()
// {
// }

// void MainWindow::setupUI()
// {
//     QWidget *centralWidget = new QWidget(this);
//     setCentralWidget(centralWidget);

//     // Create layouts for the central widget
//     QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

//     // Create search bar and buttons
//     QHBoxLayout *searchBarLayout = new QHBoxLayout();
//     QLineEdit *searchBar = new QLineEdit(this);
//     QPushButton *searchButton = new QPushButton("Search", this);
//     QPushButton *prevPageButton = new QPushButton("<< Prev Page", this);
//     QPushButton *nextPageButton = new QPushButton("Next Page >>", this);

//     searchBarLayout->addWidget(searchBar);
//     searchBarLayout->addWidget(searchButton);
//     searchBarLayout->addWidget(prevPageButton);
//     searchBarLayout->addWidget(nextPageButton);

//     // Create the grid layout for displaying posters
//     gridLayout = new QGridLayout();

//     // Add widgets to the main layout
//     mainLayout->addLayout(searchBarLayout);
//     mainLayout->addLayout(gridLayout);

//     // Connect signals to slots
//     connect(searchButton, SIGNAL(clicked()), this, SLOT(handleSearch()));
//     connect(prevPageButton, SIGNAL(clicked()), this, SLOT(handlePageNumber1()));
//     connect(nextPageButton, SIGNAL(clicked()), this, SLOT(handlePageNumber2()));
// }

// void MainWindow::displayPosters()
// {
//     // Clear any existing posters from the gridLayout
//     clearPosters();

//     // Get your movie data (e.g., from your search results)
//     cosc345::Connection con;
//     con.est_conn();
//     vector<cosc345::Connection::Movies> movies = con.getDetailMovie();

//     const int layoutCols = 3; // Number of columns in your layout
//     int row = 0;
//     int col = 0;

//     for (const auto &movie : movies)
//     {
//         QString name = QString::fromStdString(movie.title);
//         QString URL = QString::fromStdString(movie.poster);

//         // Create a QLabel to display the image
//         QPixmap presetImage("no-image-icon.png");
//         ClickableLabel *imageLabel = new ClickableLabel();
//         imageLabel->setPixmap(presetImage);

//         QObject::connect(imageLabel, &ClickableLabel::clicked, [=]()
//                          {
//                              // Handle the click event for the poster here
//                              // You can access the movie details like 'name' and 'URL'
//                          });

//         gridLayout->addWidget(imageLabel, row, col);

//         // Update the column and row for the next poster
//         col++;
//         if (col >= layoutCols)
//         {
//             col = 0;
//             row++;
//         }
//     }

//     // Update the layout
//     gridLayout->update();
// }

// void MainWindow::clearPosters()
// {
//     QLayoutItem *item;
//     while ((item = gridLayout->takeAt(0)) != nullptr)
//     {
//         QWidget *widget = item->widget();
//         if (widget)
//         {
//             // If there is a widget, remove it from the layout and delete it
//             gridLayout->removeWidget(widget);
//             delete widget;
//         }
//         // Delete the layout item
//         delete item;
//     }
// }

// void MainWindow::handleSearch()
// {
//     // Implement search functionality here
//     // Update the search results and call displayPosters()
// }

// void MainWindow::handlePageNumber1()
// {
//     // Implement logic to go to the previous page of posters
//     // Update the page number and call displayPosters()
// }

// void MainWindow::handlePageNumber2()
// {
//     // Implement logic to go to the next page of posters
//     // Update the page number and call displayPosters()
// }
