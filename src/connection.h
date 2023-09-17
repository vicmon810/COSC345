#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <random>
#include <chrono>
using namespace std;

/*!
 * @file Connection.h
 * Header file for Connection.cpp
 */
namespace cosc345
{
    /*!
     * @class Connection
     * @brief Represents a connection for reading data from a CSV file.
     */
    class Connection
    {

    private:
        int size_movie;
        int size_food;

    public:
        /*!
         *@brief Movie Struct to store movie details
         */
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

        /*!
         *@brief Food Struct to store food details
         */
        struct Food
        {
            string title;
            string ingredients;
            string directions;
            string NER;
            string food_type;
        };

        // Vector to store all movies and food
        vector<Movies> moviesDetail;
        vector<Food> foodDetail;
        /*!
         *@brief Default constructor for the Connection class.
         */
        Connection();
        /*!
        @brief reading csv file and store those data in vector
        */
        void est_conn();
        /*!
         *@brief return total movie numbers
         *@return size of total movies
         */
        int getSizeMovie();
        /*!
         *@brief return total recipe size
         *@return total size of recipe
         */
        int getSizeFood();
        /*!
         * @brief Retrieves and returns details of movies.
         * @return A vector of Movies containing movie details.
         */
        vector<Movies> getDetailMovie();
        /*!
         * @brief Retrieves and returns details of food items.
         * @return A vector of Food containing food details.
         */
        vector<Food> getDetailFood();
        /*!
         *@brief: search for matched keywords
         *@return movie contain matched keywords
         */
        vector<Movies> searching(string key);
        /*!
         *@brief Sorting movie data set by order
         *@return movie list by order
         */
        vector<Movies> sorting(string rating);

    };
}

#endif