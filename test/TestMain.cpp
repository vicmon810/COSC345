// #include "testFrontend.h"
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
}
