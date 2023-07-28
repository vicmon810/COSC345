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

    /*TESTING*/

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

    string Connection::getDetail() // chatGPT
    {
        string result;

        // Step 1: Connect to the MongoDB Atlas database
        mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

        // Step 2: Access the collection you want to query
        auto collection = conn["MOVIE_APP"]["Movies"];

        // Step 3: Define your query (e.g., find all documents)
        bsoncxx::builder::stream::document query{};
        query << bsoncxx::builder::stream::finalize;
        // cout << query << endl;
        // Step 4: Execute the query and get the cursor to the result
        auto cursor = collection.find(query.view());
        // Step 5: Iterate through the cursor to process each document
        for (const auto &doc : cursor)
        {
            // Assuming the document has a field called "title," you can access it like this: THIS DOESNT WORK
            bsoncxx::document::element titleElement = doc["title"];

            // result += bsoncxx::to_json(doc) + "\n";
        }

        return result;
    }
}