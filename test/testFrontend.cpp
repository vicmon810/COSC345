#include "testFrontend.h"
#include "testBackend.h"
#include <QTest>  // Include the Qt Test framework
#include <QTimer> // Include QTimer for delaying the exit

void testFrontend::testClickHandler()
{
    cout << "test click handler ----------------" << endl;
    vector<Connection::Movies> moviesList;
    vector<Connection::Food> foodList;
    cosc345::Connection con;
    moviesList = con.getDetailMovie();
    foodList = con.getDetailFood();
    // Initialize your moviesList and foodList with test data

    // Simulate a button click event (replace testButton with your button's actual name)
    QPushButton testButton;
    QTest::mouseClick(&testButton, Qt::LeftButton);

    // Create a Recommendation object for testing
    cosc345::Recommendation rec = cosc345::Recommendation(moviesList, foodList);
    clickHandler handler;

    // Act: Call the method you want to test.
    handler.handleItemClicked("Test Title", "Test Genres", "Test IMDB", "Test Overview", "Test Runtime", "Test Rating", "Test Release", rec);

    cout << "test click handler finished!" << endl;

    // Use a QTimer to delay the exit for a few seconds (adjust the timeout value as needed)
    QTimer::singleShot(2000, qApp, &QCoreApplication::quit); // 2000 ms = 2 seconds
}
