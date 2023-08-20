#include "Recommendation.h"


/**
 * Functions for movie and food recommendation
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

        Recommendation::Movies movie; //Return empty struct for now

        //Random select
        if (random == true) {
            //Random genre
            int random = rand() % genres.size();
            string random_genre = genres[random]; 

            //Random rating
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_real_distribution<double> distribution(0.0, 5.0); 
            double random_rating = distribution(gen);  

            //Select random movie
            bool check = false;
            while (check) {
                //Select movie based on random genre and rating
                check = false; // to not start infinite loop for now
            }
        }

        //Loop through movie struct vector and append genres and ratings related to that

        return movie; //Return empty struct for now

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

