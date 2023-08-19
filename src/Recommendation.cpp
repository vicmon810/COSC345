#include "Recommendation.h"

using namespace std;

/**
 * Functions for connecting to mongodb atlas database
 */
namespace cosc345
{
    //Default constructor
    Recommendation::Recommendation() {}

    /**
    * Method for the conditional select mode
    */
    Recommendation::Movies conditional(vector<string> genres, vector<double> rating, bool random) {

        //separate vector of movies
        vector<Connection::Movies> sorted;

        //Random select
        if (random == true) {

        }

        //Loop through movie struct vector and append genres and ratings related to that

        Recommendation::Movies movie; //Return empty struct for now

        return movie;

    }

    /**
    * Method for the conditional select mode
    */
    Recommendation::Movies tournament(vector<string> genres, vector<double> rating, bool random) {
        Recommendation::Movies movie; //Return empty struct for now

        return movie;
    }


    /**
    * Method to return random food
    */
    Recommendation::Food randomfoodSelect() {
        Recommendation::Food food; //Return empty struct for now

        return food;
    }
}

