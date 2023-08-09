/***
 * https://cpp.hotexamples.com/examples/-/QMenu/-/cpp-qmenu-class-examples.html
 */
#include <iostream>
#include "Connection.h"
#include "GUI.h"
#include <QApplication>
#include <QPushButton>
#include <QMenu>
#include <QObject>
#include <QFrame>
#include <QHBoxLayout>
#include <QTextFormat>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
/**
 * Main file to run everything
 */
int main(int argc, char **argv) // As GUI thing needs this apparently
{
    using namespace std;
    using namespace cosc345;

    QApplication app(argc, argv);
    QPushButton button("Click Me");
    QFrame frame;

    // QLineEdit text(movie);
    // Init QMenu
    QMenu *menu = new QMenu();
    menu->setTitle(QObject::tr("Movie and Food"));
    // Add new Options
    menu->addAction(QObject::tr("I Feel Luck"));
    menu->addAction(QObject::tr("Open"));
    menu->addAction(QObject::tr("Save"));
    // Sub----Menu
    QMenu *submenu = menu->addMenu(QObject::tr("Settings"));
    submenu->addAction(QObject::tr("Preferences"));
    submenu->addAction(QObject::tr("Language"));

    // frame.setHidden(menu);
    // Layout for virtual display
    QHBoxLayout *layout = new QHBoxLayout;
    // layout for horntail displayy
    QVBoxLayout *layout_v = new QGridLayout;
    // add menu into frame virtual
    layout->addWidget(menu);
    layout->addSpacing(10);

    // Connecting into DB
    Connection conn;
    conn.est_conn();
    // conn.getDetailMovie();
    // Initial Qt Objects
    QCheckBox *checkBox = new QCheckBox();
    QLineEdit *lineEdit = new QLineEdit();

    // Fill words in CheckBOX
    checkBox->setText("Movie Size: " + QString::number(conn.getSizeMovie()));
    checkBox->setChecked(true);


    // File detials
    vector<cosc345::Connection::Movies> moviesDetail = conn.getDetailMovie();
    QString movieDetailsString;
    int row = 0;
    for (const auto &movie : moviesDetail) // AI
    {
        // assign movies infor to lables
        QLabel *titleLabel = new QLabel("Title: " + movie.title);
        QLabel *genreLalbe = new QLabel("Genre: " + movie.genres);
        QLabel *imdbLabel = new QLabel("IMDB ID:" + movie.imdb_id);
        QLabel *overviewLabel = new QLabel("Overview: " + movie.overview);
        QLabel *releaseLabel = new QLabel("Release Date: " + QString::number(movie.release_date));
        QLabel *runtimeLabel = new QLabel("Runtime: " + QString::number(movie.runtime));
        QLabel *ratingLabel = new QLabel("Rating: " + QString::number(movie.rating));
        // aligning each label
        layout_v->addWidget(titleLabel)
        layout_v->addWidget(genreLalbe);
        layout_v->addWidget(imdbLabel);
        layout_v->addWidget(overviewLabel);
        layout_v->addWidget(releaseLabel);
        layout_v->addWidget(runtimeLabel);
        layout_v->addWidget(ratingLabel);
        row++;
    }

    // alignments
    layout->addLayout(layout_v);
    layout_v->addWidget(checkBox);
    layout_v->addSpacing(100);
    layout_v->addWidget(lineEdit);

    // display frame
    frame.setLayout(layout);
    frame.show();
    return app.exec();
    // return 0;
}