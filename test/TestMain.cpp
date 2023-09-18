#include "testFrontend.h"
#include "testBackend.h"
#include <QTimer>
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    std::cout << "Running tests...\n";
    cosc345::testBackend test1;
    // Call the test functions
    test1.testGetSizeMovies();
    test1.testSearching();
    test1.testGetFoodSize();
    test1.testRecommendation();
    testFrontend test2;
    QApplication app(argc, argv);

    // Create the main window
    QWidget mainWindow;
    mainWindow.setWindowTitle("Auto Clicker Example");
    mainWindow.setGeometry(100, 100, 400, 200);

    // Create an "Exit" button

    QTimer timer;
    timer.setSingleShot(true); // Run only once
    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {
                         cout << "Test" << endl;
                        test2.testClickHandler();
                        app.quit(); });
    timer.start(1000); // 1000 ms = 1 second

    mainWindow.show();

    // If no assertion errors occurred, tests passed
    std::cout << "All tests passed!\n";

    return app.exec();
}
