#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "Connection.h"

using namespace std;

/**
 * Functions for connecting to mongodb atlas database
 */
namespace cosc345
{
    Connection::Connection() {}

    void Connection::est_conn()
    {
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

        bsoncxx::builder::stream::document document{};
        auto collection_movie = conn["MOVIE_APP"]["Movies"];
        auto collection_food = conn["MOVIE_APP"]["Recipe"];
        size_movie = 0;
        size_food = 0;
        auto cursor_movie = collection_movie.find({});
        auto cursor_food = collection_food.find({});
        for (auto &&doc : cursor_movie)
        {
            size_movie++;
        }
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
    // string Connection::getDetial()
    //{
    // }
}