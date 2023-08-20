#ifndef RECOMMENDATION_H_INCLUDED
#define RECOMMENDATION_H_INCLUDED

#include "connection.h"
#include <random>

using namespace std;

/**
 * Header file for Connection.cpp
 */
namespace cosc345
{
    class Recommendation
    {

    private:
        // Vector to store all movies and food
        vector<cosc345::Connection::Movies> moviesDetail;
        vector<cosc345::Connection::Food> foodDetail;

        //Genre vector 
        vector<string> genres = { "Action", "Adventure", "Family",
                                 "Fantasy" , "Crime", "Drama"
                                 "Comedy", "Horror", "Sci-Fi", 
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
            int release_date;
            int runtime;
            string title;
            double rating;
        };

        // Food Struct
        struct Food
        {
            string title;
            string ingredients;
            string directions;
            string NER;
        };

        //Default constructor
        Recommendation();
        
        //Recommendation modes
        Movies conditional(vector<string> genres, vector<double> rating, bool random);
        Movies tournament(vector<string> genres, vector<double> rating, bool random);

        //Food stuff
        //Later


    };
}

#endif