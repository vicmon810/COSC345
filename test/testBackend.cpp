#include "testBackend.h"
#include "TestFrontend.h"
void cosc345::testBackend::testGetSizeMovies()
{
    cosc345::Connection con;
    con.est_conn();
    int movieCount = con.getSizeMovie();
    assert(movieCount != 0 && "getSizeMovie returned zero");

    std::cout << "Test for getSizeMovies passed. Movie count: " << movieCount << std::endl;
}

void cosc345::testBackend::testSearching()
{
    cosc345::Connection con;
    con.est_conn();

    string searchTerm1 = "joker";
    vector<cosc345::Connection::Movies> searchResult1 = con.searching(searchTerm1);
    assert(!searchResult1.empty() && "No results found for Joker");
    cout << "Test for searching with '" << searchTerm1 << "' passed. Found " << searchResult1.size() << " results." << endl;

    string searchTerm2 = "not_existing_movies";
    vector<cosc345::Connection::Movies> searchResult2 = con.searching(searchTerm2);
    cout << searchResult2.empty() << endl;cd
    assert(searchResult2.empty() && "Unexpected results found for NonExistentMovie");
    cout << "Test for searching with" << searchTerm2 << " Passed." << endl;
}

void cosc345::testBackend::testRecommendation()
{
    // Create some test data
    vector<Connection::Movies> moviesList;
    vector<Connection::Food> foodList;

    // Initialize your moviesList and foodList with test data

    // Create a Recommendation object for testing
    cosc345::Recommendation recommender(moviesList, foodList);

    // Test getGenres()
    vector<string> genres = recommender.getGenres();
    assert(!genres.empty() && "Genres list is empty");

    // Test movieSelect()
    // vector<string> selectedGenres;
    // selectedGenres.push_back("Drama");
    // selectedGenres.push_back("Action");
    // double selectedRating = 7.0;
    // Connection::Movies selectedMovie = recommender.movieSelect(selectedGenres, selectedRating);
    // assert(!selectedMovie.title.empty() && "No movie selected");

    // // Test randomMovieSelect()
    // Connection::Movies randomSelectedMovie = recommender.randomMovieSelect();
    // assert(!randomSelectedMovie.title.empty() && "No random movie selected");

    // // Test savouryFoodSelect()
    // Connection::Food savouryFood = recommender.savouryFoodSelect();
    // assert(!savouryFood.title.empty() && "No savoury food selected");

    // // Test sweetFoodSelect()
    // Connection::Food sweetFood = recommender.sweetFoodSelect();
    // assert(!sweetFood.title.empty() && "No sweet food selected");
}
