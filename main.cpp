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
#include <QVBoxLayout>
/**
 * Main file to run everything
 */
int main(int argc, char **argv) // As GUI thing needs this apparently
{
    using namespace std;
    using namespace cosc345;

    // Initialise QT App
    // QApplication app(argc, argv);

    // Test connection to database
    Connection conn;
    conn.est_conn();
    cout << "Total Moive: " << conn.getSizeMovie() << endl;
    cout << "Total Recipe: " << conn.getSizeFood() << endl;
    // cout << "detail" << conn.getDetail() << endl;
    //  GUI button;
    //  button.slots();
    int movie = conn.getSizeMovie();
    // Initialise QT App
    QApplication app(argc, argv);
    // QPushButton button("Click Me");
    QFrame frame;

    // QLineEdit text(movie);
    // Init QMenu
    QMenu *menu = new QMenu();
    menu->setTitle(QObject::tr("File"));
    // Add new Options
    menu->addAction(QObject::tr("New"));
    menu->addAction(QObject::tr("Open"));
    menu->addAction(QObject::tr("Save"));
    // Sub----Menu
    QMenu *submenu = menu->addMenu(QObject::tr("Settings"));
    submenu->addAction(QObject::tr("Preferences"));
    submenu->addAction(QObject::tr("Language"));
    // SHOW!!!!
    // menu->exec(QCursor::pos());
    // button.show();
    // text.show();
    // frame.setHidden(menu);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(menu);
    frame.setLayout(layout);
    frame.show();
    return app.exec();
    return 0;
}