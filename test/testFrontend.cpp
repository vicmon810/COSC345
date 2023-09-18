#include "testFrontend.h"

void testFrontend::testClickHandler()
{
    cout << "test click handler ----------------" << endl;
    vector<Connection::Movies> moviesList;
    vector<Connection::Food> foodList;
    cosc345::Connection con;
    moviesList = con.getDetailMovie();
    foodList = con.getDetailFood();
    // Initialize your moviesList and foodList with test data

    // Create a Recommendation object for testing
    cosc345::Recommendation rec = cosc345::Recommendation(moviesList, foodList);
    clickHandler handler;
    // Act: Call the method you want to test.
    handler.handleItemClicked("Test Title", "Test Genres", "Test IMDB", "Test Overview", "Test Runtime", "Test Rating", "Test Release", rec);

    cout << "test click handler finished!" << endl;
}
