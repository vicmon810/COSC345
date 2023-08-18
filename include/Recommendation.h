#ifndef RECOMMENDATION_H_INCLUDED
#define RECOMMENDATION_H_INCLUDED

#include "Connection.h"
#include <random>
#include <ctime>

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

        //Variables for random selection
        default_random_engine rng;

        //list of possible genres
        vector<string> genres = { "Action", "Adventure", "Fantasy", "Animation", 
                                  "Horror", "Comedy", "Thriller", "ScienceFiction"
        };

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

        //Default constructor
        Recommendation();
        
        //Recommendation modes
        Movies conditional(vector<string> genres, vector<double> rating, bool random);
        Movies tournament(vector<string> genres, vector<double> rating, bool random);

        //Food stuff
        Food randomfoodSelect(); //Returns random food for a start


    };
}

#endif