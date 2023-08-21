#include <iostream>
#include <cassert>
#include "../src/connection.h"
// Define a custom test runner function

void con_estTest(cosc345::Connection con)
{
    con.est_conn();
}
/**!
 * test getSizeMovies function return right value
 */
void readTest()
{
    cosc345::Connection con;
    // con_estTest(con);
    con.est_conn();
    int movieCount = con.getSizeMovie();
    // cout << movieCount << endl;
    assert(movieCount != 0);                       // movie  is not 0
    assert(movieCount == con.moviesDetail.size()); // movieDetail have same number of movieCount
}

int main()
{
    std::cout << "Running tests...\n";

    // Call the read movie function
    readTest();

    // If no assertion errors occurred, tests passed
    std::cout << "All tests passed!\n";

    return 0;
}
