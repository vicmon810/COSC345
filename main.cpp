#include <iostream>
#include "Connection.h"
// #include "GUI.h"
int main()
{
    using namespace std;
    using namespace cosc345;
    Connection conn;
    conn.est_conn();
    cout << "Total Moive: " << conn.getSizeMovie() << endl;
    cout << "Total Recipe: " << conn.getSizeFood() << endl;
    // GUI button;
    // button.slots();
    return 0;
}