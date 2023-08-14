// import catch hearder file
#include <cache.h>
// include h file
// #include <bsoncxx/builder/stream/document.hpp>
#include "../include/Connection.h"

// Define test cases
TESE_CASE("Connection class tests", "[Connection]")
{
    // create an instance of teh Connection class
    cosc345::Connection connection;
    SECTION("Check inital size of movies and food vectors")
    {
        REQUIRE(connection.getSizeMoive() == 0); // true
        REQUIRE(connection.getSizeFood() == 0);  // true
    }
    SECTION("TEST est_conn method")
    {
        // test est_conn method
        connection.est_conn();
        REQUIRE(Connection.getSizeMovie() > 0);
        REQUIRE(Connection.getSizeFood() > 0);
        REQUIRE(connection.getDetailMovie().size() == connection.getSizeMovie());
        REQUIRE(connection.getDetailFood().size() == connection.getSizeFood());
    }
}