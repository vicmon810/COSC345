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

        // Vector to store all movies and food
        vector<Connection::Movies> moviesList;
        vector<Connection::Food> savouryFoodList;
        vector<Connection::Food> sweetFoodList;

        /*!
         *@brief Default constructor of Recommendation
         */
        Recommendation();

        /*!
<<<<<<< HEAD
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
=======
        * @brief Constructor of Recommendation that takes in 
        * @param Connection object conn
        */
        Recommendation(vector<Connection::Movies> moviesList, vector<Connection::Food> foodList);

        /*!
        * @brief Accessor for the genres vector for the Recommendation class. Could set to public but I don't like having all the variables
        * public. Might not even be used.
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
        Connection::Movies movieSelect(vector<string> genres, double rating); 

        /*!
        * @brief Function to return a random movie struct from moviesList vector
        * @param genres String vector of genres
        * @param rating rating of movie in a double type
        * @return movie struct containing movie details
        */
        Connection::Movies randomMovieSelect();
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657

        /*!
        *@brief Function to return a savoury food in the foodDetails vector
        *@return food details of a savoury food in the foodDetails vector
        */
        Connection::Food savouryFoodSelect();

        /*!
        *@brief Function to return a sweet food in the foodDetails vector
        *@return food details of a sweet food in the foodDetails vector
        */
        Connection::Food sweetFoodSelect();
    };
}

#endif