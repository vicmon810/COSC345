#include "Connection.h"

using namespace std;

/**
 * Functions for connecting to mongodb atlas database
 */
namespace cosc345
{
    Connection::Connection() {}

    /*TESTING*/

    void Connection::est_conn()
    {
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

        bsoncxx::builder::stream::document document{};
        collection_movie = conn["MOVIE_APP"]["Movies"];
        collection_food = conn["MOVIE_APP"]["Recipe"];
        size_movie = 0;
        size_food = 0;
        auto cursor_movie = collection_movie.find({});
        auto cursor_food = collection_food.find({});
        moviesDetail;
        // count for movie size
        for (auto &&doc : cursor_movie)
        {
            size_movie++;
            Movies movie;
            if (doc["title"])
                movie.title = doc["title"].get_utf8().value.to_string();
            if (doc["genres"])
                movie.genres = doc["genres"].get_utf8().value.to_string();
            if (doc["imdb_id"])
                movie.imdb_id = doc["imdb_id"].get_utf8().value.to_string();
            if (doc["overview"])
                movie.overview = doc["overview"].get_utf8().value.to_string();
            if (doc["release_date"])
                movie.release_date = doc["release_date"].get_int32().value;
            if (doc["runtime"])
                movie.runtime = doc["runtime"].get_int32().value;
            if (doc["rating"])

                movie.rating = doc["rating"].get_double().value;

            moviesDetail.push_back(movie);
        }
        cout << moviesDetail.size() << endl;
        // count for food size
        for (auto &&doc : cursor_food)
            size_food++;
    }

    /*
    @Desc:return total size of the movied data set
    */
    int Connection::getSizeMovie()
    {
        return size_movie;
    }

    /*
    @Desc:return total size of the food in data set
    */
    int Connection::getSizeFood()
    {
        return size_food;
    }

    void Connection::getDetailMovie()
    {
        // C++ build memory management

        auto cursor_movie = collection_movie.find({});
    }
}