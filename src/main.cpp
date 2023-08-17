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
#include "../include/Connection.h"
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // initialize QFrame
    QFrame frame;
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    frame.setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame.setLineWidth(2);
    // Set the default size of QFrame
    // QVBoxLayout *layout = new QVBoxLayout;

    // initialize menu
    QMenu *menu = new QMenu();
    menu->setTitle(QObject::tr("Movie and Food"));
    menu->addAction(QObject::tr("I Feel Lucky"));
    menu->addAction(QObject::tr("Open"));
    menu->addAction(QObject::tr("Save"));
    QMenu *submenu = menu->addMenu(QObject::tr("Settings"));
    submenu->addAction(QObject::tr("Preferences"));
    submenu->addAction(QObject::tr("Language"));

    // Initialize layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *movieLayout = new QGridLayout;

    // Query data from back-end
    cosc345::Connection conn;
    conn.est_conn();
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();

    // Initialize QList to for display data set
    QListWidget *listWidget = new QListWidget();

    for (const cosc345::Connection::Movies &movie : movies)
    {
        QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
                               "Genres: " + QString::fromStdString(movie.genres) + "\n" + "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" + "Overview: " + QString::fromStdString(movie.overview) + "\n" + "Release Date: " + QString::number(movie.release_date) + "\n" + "Runtime: " + QString::number(movie.runtime) + "\n" + "Rating: " + QString::number(movie.rating) + "\n" + "Food: Popcorn";
        // we only display 50 chars
        const int maxDisplayLen = 50;
        if (movieDetails.length() > maxDisplayLen)
        {
            movieDetails.truncate(maxDisplayLen); // Truncate the string
            movieDetails += "...";                // Add ellipses to indicate truncation
        }

        QListWidgetItem *item = new QListWidgetItem(movieDetails);
        item->setSizeHint(QSize(75, 75)); // Set the size of each card
        listWidget->addItem(item);
        // Add a separator line
    }
    // Append menu/Qlist on main layout
    // mainLayout->addWidget(&frame);
    mainLayout->addWidget(menu);
    movieLayout->addWidget(listWidget);
    mainLayout->addLayout(movieLayout);
    movieLayout->addWidget(line);
    // display manLayout
    frame.setLayout(mainLayout);
    frame.show();

    return app.exec();
}
