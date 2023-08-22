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
     *@brief TODO
     */
    class Recommendation
    {

    private:
        // Vector to store all movies and food
        vector<cosc345::Connection::Movies> moviesDetail;
        vector<cosc345::Connection::Food> foodDetail;

        // Genre vector
        vector<string> genres = {"Action", "Adventure", "Family",
                                 "Fantasy", "Crime", "Drama"
                                                     "Comedy",
                                 "Horror", "Sci-Fi",
                                 "ScienceFiction", "Romance", "Thriller",
                                 "War", "Documentary", "Mystery",
                                 "Music", "Western"};

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
        };

        // Food Struct
        struct Food
        {
            string title;
            string ingredients;
            string directions;
            string NER;
        };

        /*!
         *@brief Default constructor of Commendation
         */
        Recommendation();

        // Recommendation modes
        Movies conditional(vector<string> genres, vector<double> rating, bool random);
        Movies tournament(vector<string> genres, vector<double> rating, bool random);

        // Food stuff
        // Later
    };
}

#endif