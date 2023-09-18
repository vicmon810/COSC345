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

    // testFrontend test2;
    // QApplication app(argc, argv);

    // // Start a QTimer to exit the application after 2 seconds (2000 ms)
    // QTimer exitTimer;
    // exitTimer.setSingleShot(true);
    // QObject::connect(&exitTimer, &QTimer::timeout, [&]()
    //                  {
    //                      std::cout << "\nAll tests passed!\n";
    //                      app.quit(); // Quit the application after tests are done
    //                  });
    // exitTimer.start(2000); // 2000 ms = 2 seconds

    // test2.testClickHandler();

    // return app.exec(); // Start the Qt event loop
}
