#include <iostream>
#include "Connection.h"
#include "GUI.h"
#include <QApplication>
#include <QPushButton>
/**
 * Main file to run everything
 */
int main(int argc, char **argv) // As GUI thing needs this apparently
{
    using namespace std;
    using namespace cosc345;

    // Test connection to database
    Connection conn;
    conn.est_conn();
    cout << "Total Moive: " << conn.getSizeMovie() << endl;
    cout << "Total Recipe: " << conn.getSizeFood() << endl;
    // cout << "detail" << conn.getDetail() << endl;
    //  GUI button;
    //  button.slots();
    int movie = conn.getSizeMovie();
    QApplication app(argc, argv);
    QPushButton button("Click Me");
    button.show();
    return app.exec();
    return 0;
}