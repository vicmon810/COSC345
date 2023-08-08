#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std;

/**
 * Header file for Connection.cpp
 */
namespace cosc345
{
    class Connection
    {

    private:
        mongocxx::collection collection_movie;
        mongocxx::collection collection_food;
        string result;
        int size_movie;
        int size_food;

        // comment

    public:
        struct Movies
        {
            string genres;
            string imdb_id;
            string overview;
            int release_date;
            int runtime;
            string title;
            double rating;
        };
        vector<Movies> moviesDetail;
        Connection();
        void est_conn();
        int getSizeMovie();
        int getSizeFood();
        vector<Movies> getDetailMovie();
    };
}

#endif