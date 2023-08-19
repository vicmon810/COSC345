#include "Recommendation.h"
#include "Connection.h"
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
#include <iostream> //test, delete after use
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>

/*Should display full movied detial not truncate data set*/
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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // initialize QFrame
    QFrame frame;

    // Query data from back-end
    cosc345::Connection conn;
    conn.est_conn();
    // Get movie and food vector structs
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();
    // vector<cosc345::Connection::Food> food = conn.getDetailFood();

    // Initialize QList to for display data set
    QListWidget *listWidget = new QListWidget();

    for (const cosc345::Connection::Movies &movie : movies)
    {
        QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
                               "Genres: " + QString::fromStdString(movie.genres) + "\n" +
                               "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" +
                               "Overview: " + QString::fromStdString(movie.overview) + "\n" +
                               "Release Date: " + QString::fromStdString(movie.release_date) + "\n" +
                               "Runtime: " + QString::fromStdString(movie.runtime) + "\n" +
                               "Rating: " + QString::fromStdString(movie.rating) + "\n" + // Convert double to QString
                               "Food: Popcorn\n" +
                               "Poster: " + QString::fromStdString(movie.poster);

        // we only display 50 chars const int maxDisplayLen = 50;
        // if (movieDetails.length() > 50)
        // {
        //     movieDetails.truncate(maxDisplayLen); // Truncate the string
        //     movieDetails += "...";                // Add ellipses to indicate truncation
        // }

        QListWidgetItem *item = new QListWidgetItem(movieDetails);
        item->setSizeHint(QSize(75, 75)); // Set the size of each card
        listWidget->addItem(item);
        // Connect the itemClicked signal to the handleItemClicked slot
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
