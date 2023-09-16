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
            string food_type;
        };

        // Vector to store all movies and food
        vector<Movie> moviesList;
        vector<Food> savouryFoodList;
        vector<Food> sweetFoodList;

        /*!
         *@brief Default constructor of Recommendation
         */
        Recommendation();

        /*!
         * @brief Constructor of Recommendation that takes in
         * @param Connection object conn
         */
        Recommendation(Connection conn);

        /*!
         * @brief Accessor for the genres vector for the Recommendation class. Could set to public but I don't like having all the variables
         * public.
         * @return genres vector of genre strings
         */
        vector<string> getGenres() const;

        /*!
         * @brief Function to return movie struct from moviesList vector that matches
         * genres and rating parameters
         * @param genres String vector of genres
         * @param rating rating of movie in a double type
         * @return movie struct containing movie details
         */
        Movie movieSelect(vector<string> genres, double rating);

        /*!
         * @brief Function to return a random movie struct from moviesList vector
         * @param genres String vector of genres
         * @param rating rating of movie in a double type
         * @return movie struct containing movie details
         */
        Movie randomMovieSelect();

        /*!
        *@brief Function to return a savoury food in the foodDetails vector
        *@return food details of a savoury food in the foodDetails vector
        */
        Food savouryFoodSelect(vector<Food> foodlist);

        /*!
        *@brief Function to return a sweet food in the foodDetails vector
        *@return food details of a sweet food in the foodDetails vector
        */
        Food sweetFoodSelect(vector<Food> foodlist);
    };
}

#endif