#include "test.h"

void testGetSizeMovies()
{
    cosc345::Connection con;
    con.est_conn();
    int movieCount = con.getSizeMovie();
    assert(movieCount != 0 && "getSizeMovie returned zero");

    std::cout << "Test for getSizeMovies passed. Movie count: " << movieCount << std::endl;
}

void testSearching()
{
    cosc345::Connection con;
    con.est_conn();

    string searchTerm1 = "joker";
    vector<cosc345::Connection::Movies> searchResult1 = con.searching(searchTerm1);
    assert(!searchResult1.empty() && "No results found for Joker");
    cout << "Test for searching with '" << searchTerm1 << "' passed. Found " << searchResult1.size() << " results." << endl;

    string searchTerm2 = "not_existing_movies";
    vector<cosc345::Connection::Movies> searchResult2 = con.searching(searchTerm2);
    cout << searchResult2.empty() << endl;
    assert(searchResult2.empty() == 0 && "Unexpected results found for NonExistentMovie");
    cout << "Test for searching with" << searchTerm2 << " Passed." << endl;
}
void TestRecommendation()
{
    cosc345::Connection con;
    cosc345::Recommendation recommender(con);

    vector<string> genres = recommender.getGenres();
    assert(!genres.empty() && "Genres list is empty");
    vector<string> selectedGenres;
    selectedGenres.push_back("Drama");
    selectedGenres.push_back("Action");
    double selectedRating = 7.0;
    cosc345::Recommendation::Movie selectedMovie = recommender.movieSelect(selectedGenres, selectedRating);
    assert(selectedMovie.title != "" && "No movie selected");

    // Test randomMovieSelect function
    cosc345::Recommendation::Movie randomSelectedMovie = recommender.randomMovieSelect();
    assert(randomSelectedMovie.title != "" && "No random movie selected");
}

int main()
{
    cout << "Running tests...\n";

    // Call the read movie function
    testGetSizeMovies();
    testSearching();

    // If no assertion errors occurred, tests passed
    cout
        << "All tests passed!\n";

    return 0;
}
