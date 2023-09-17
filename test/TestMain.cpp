#include "testBackend.h"
int main()
{
    std::cout << "Running tests...\n";
    cosc345::testBackend test1;
    // Call the test functions
    test1.testGetSizeMovies();
    test1.testSearching();
    test1.testRecommendation();

    // If no assertion errors occurred, tests passed
    std::cout << "All tests passed!\n";

    return 0;
}