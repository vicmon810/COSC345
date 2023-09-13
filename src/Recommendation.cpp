#include "Recommendation.h"

/**
 * Functions for movie and food recommendation
 */
namespace cosc345
{
    //Default constructor
    Recommendation::Recommendation() {}

    void Recommendation::init() {
        //Create own connection class
        Connection conn; 
        conn.est_conn(); 

        vector<Connection::Movies> movies = conn.getDetailMovie(); 
        vector<Connection::Food> moviesfoodDetail = conn.getDetailFood(); 

        //Transfer Connection::Movies to Recommendation::Movie since they are from
        //different classes. So I dont have to use Connection:: Connection:: Connection::
        //for everything I do in recommendation.cpp. Also the recommendation functions
        //cant really return a Connection:: item in a Recommendation:: function, C++ is ass
        for (const cosc345::Connection::Movies& mov : movies) 
        {
            //Initialise movie
            Recommendation::Movie movie;
            //Transfer data into movie
            movie.genres = mov.genres;
            movie.poster = mov.poster;
            movie.imdb_id = mov.imdb_id;
            movie.overview = mov.overview;
            movie.release_date = mov.release_date;
            movie.runtime = mov.runtime;
            movie.title = mov.title;
            movie.rating = mov.rating;

            moviesList.push_back(movie);
        }

        //Do it for food as well
        //coming soon
    }

    Recommendation::Movie movieSelect(vector<string> genres, double rating) {

        //separate vector of movies
        vector<Connection::Movies> sorted;

        Recommendation::Movie movie; //Return empty struct for now

        //Loop through movie struct vector and append genres and ratings related to that

        return movie; //Return empty struct for now

    }

    Recommendation::Movie randomMovieSelect(vector<string> genres, double rating) {
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

        Recommendation::Movie movie; //Return empty struct for now 

        return movie; //Return empty struct for now 
    }

    /**
    * Method to return random food
    */
    Recommendation::Food randomfoodSelect() {
        Recommendation::Food food; //Return empty struct for now

        return food;
    }
}

