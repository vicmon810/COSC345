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
 /**
  * Main file to run everything
  */
int main(int argc, char** argv) // As GUI thing needs this apparently
{
    using namespace std;
    using namespace cosc345;

    // Initialise QT App
    // QApplication app(argc, argv);

    // Test connection to database
    // Connection conn1;
    // conn1.est_conn();
    // conn1.getDetailMovie();
    // cout << "Total Moive: " << conn.getSizeMovie() << endl;
    // cout << "Total Recipe: " << conn.getSizeFood() << endl;
    // cout << "detail" << conn.getDetail() << endl;
    //  GUI button;
    //  button.slots();
    // Initialise QT App
    QApplication app(argc, argv);
    QPushButton button("Click Me");
    QFrame frame;

    // QLineEdit text(movie);
    // Init QMenu
    QMenu* menu = new QMenu();
    menu->setTitle(QObject::tr("Movie and Food"));
    // Add new Options
    menu->addAction(QObject::tr("I Feel Luck"));
    menu->addAction(QObject::tr("Open"));
    menu->addAction(QObject::tr("Save"));
    // Sub----Menu
    QMenu* submenu = menu->addMenu(QObject::tr("Settings"));
    submenu->addAction(QObject::tr("Preferences"));
    submenu->addAction(QObject::tr("Language"));

    // frame.setHidden(menu);
    // Layout for virtual display
    QHBoxLayout* layout = new QHBoxLayout;
    // layout for horntail displayy
    QVBoxLayout* layout_v = new QVBoxLayout;
    // add menu into frame virtual
    layout->addWidget(menu);
    layout->addSpacing(10);

    // Connecting into DB
    Connection conn;
    conn.est_conn();
    // conn.getDetailMovie();
    // Initial Qt Objects
    QCheckBox* checkBox = new QCheckBox();
    QLineEdit* lineEdit = new QLineEdit();

    // Fill words in CheckBOX
    checkBox->setText("Movie Size: " + QString::number(conn.getSizeMovie()));
    checkBox->setChecked(true);

    // Fill words in lineEdit with read only
    lineEdit->setText("Receipt Size: " + QString::number(conn.getSizeFood()));
    lineEdit->setReadOnly(true);

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