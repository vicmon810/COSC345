#include "../include/Connection.h"
<<<<<<< HEAD
// #include
using namespace std;
=======
>>>>>>> 0930304a6c892ff294bb1f49c6a8e780a37c0fa3

/**
 * Functions for connecting to mongodb atlas database
 */
namespace cosc345
{
    Connection::Connection() {}

    /**
     * Connect to MongoDB and get all the data
     */
    void Connection::est_conn()
    {
        // Establish connection
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

        bsoncxx::builder::stream::document document{};
        collection_movie = conn["MOVIE_APP"]["Movies"];
        collection_food = conn["MOVIE_APP"]["Food"];
        size_movie = 0;
        size_food = 0;
        auto cursor_movie = collection_movie.find({});
        auto cursor_food = collection_food.find({});

        // count for movie size
        for (auto &&doc : cursor_movie)
        {
            size_movie++;
            // std::cout << bsoncxx::to_json(doc) << std::endl;
            // Instance of struct
            Movies movie;
            // If statements are needed to check if the column still exists
            if (doc["title"])
                movie.title = string(doc["title"].get_utf8().value);
            if (doc["genres"])
                movie.genres = string(doc["genres"].get_utf8().value);
            if (doc["imdb_id"])
                movie.imdb_id = string(doc["imdb_id"].get_utf8().value);
            if (doc["overview"])
                movie.overview = string(doc["overview"].get_utf8().value);
            if (doc["release_date"])
                movie.release_date = string(doc["release_date"].get_utf8().value);
            if (doc["runtime"])
                movie.runtime = doc["runtime"].get_int32();
            if (doc["rating"])
                movie.rating = doc["rating"].get_double();
            if (doc["poster"])
                movie.poster = string(doc["poster"].get_utf8().value);
            else
                movie.poster = "";

            moviesDetail.push_back(movie);
        }

        // count for food size
        for (auto &&doc : cursor_food)
        {
            size_food++;
            // Instance of struct
            Food food;
            // If statements are needed to check if the column still exists
            if (doc["title"])
                food.title = string(doc["title"].get_utf8().value);
            if (doc["ingredients"])
                food.ingredients = string(doc["ingredients"].get_utf8().value);
            if (doc["directions"])
                food.directions = string(doc["directions"].get_utf8().value);
            if (doc["NER"])
                food.NER = string(doc["NER"].get_utf8().value);

            foodDetail.push_back(food);
        }
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

    /**
     * Returns the details of all movies
     */
    vector<Connection::Movies> Connection::getDetailMovie()
    {
        return moviesDetail;
    }

    /**
     * Returns the details of all food
     */
    vector<Connection::Food> Connection::getDetailFood()
    {
        return foodDetail;
    }
}