#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Header file for Connection.cpp
 */
namespace cosc345
{
    class Connection
    {

    private:
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
            string runtime;
            string title;
            string rating;
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