#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "Connection.h"

using namespace std;

namespace cosc345
{
    Connection::Connection() {}

    void Connection::est_conn()
    {
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

        bsoncxx::builder::stream::document document{};
        auto collection = conn["MOVIE_APP"]["Movies"];

        long size = 0;

        auto cursor = collection.find({});

        for (auto &&doc : cursor)
        {
            size++;
        }
        cout << size << endl;
    }
}