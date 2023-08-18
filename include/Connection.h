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

    public:
        // Movie struct
        struct Movies
        {
            string genres;
            string imdb_id;
            string overview;
            string release_date;
            int runtime;
            string title;
            double rating;
            string poster;
        };

        // Food Struct
        struct Food
        {
            string title;
            string ingredients;
            string directions;
            string NER;
        };

        // Vector to store all movies and food
        vector<Movies> moviesDetail;
        vector<Food> foodDetail;

        Connection();
        void est_conn();
        int getSizeMovie();
        int getSizeFood();
        vector<Movies> getDetailMovie();
        vector<Food> getDetailFood();
    };
}

#endif