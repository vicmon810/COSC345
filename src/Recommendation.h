#ifndef RECOMMENDATION_H_INCLUDED
#define RECOMMENDATION_H_INCLUDED

#include "connection.h"
#include <random>

using namespace std;

/*!
 *@file recommendation.h
 *header file of recommendation.cpp
 */
namespace cosc345
{
    /*!
     *@class Recommendation
     *@brief class to house recommendation functions needed for the beta version, this includes the main 2
     * recommendation features of the application.
     */
    class Recommendation
    {

    private:
        // Genre vector
        vector<string> genres = {"Action", "Adventure", "Family",
                                 "Fantasy", "Crime", "Drama", 
                                 "Comedy", "Horror", "Sci-Fi",
                                 "ScienceFiction", "Romance", "Thriller",
                                 "War", "Documentary", "Mystery",
                                 "Music", "Western"};


    public:
        /*!
         *@brief Movie Struct to store movie details
         */
        struct Movie
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
        };

        // Vector to store all movies and food
        vector<Movie> moviesList;
        vector<Food> foodList;

        /*!
         *@brief Default constructor of Recommendation
         */
        Recommendation();

        /*!
        * @brief Init function of Recommendation
        */
        void init();

        // Recommendation modes
        Movie movieSelect(vector<string> genres, double rating); 
        Movie randomMovieSelect(vector<string> genres, double rating);

        /*!
        *@brief Function to return a random food in the foodDetails vector
        *@return food details in a random element in the foodDetails vector
        */
        Food randomFoodSelect();
    };
}

#endif