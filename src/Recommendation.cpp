#include "Recommendation.h"

/**
 * Functions for movie and food recommendation
 */
namespace cosc345
{
    //Default constructor
    Recommendation::Recommendation() {}

    Recommendation::Recommendation(Connection conn) {
        //Add to vector
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

    vector<string> Recommendation::getGenres() const {
        return this->genres;
    }

    Recommendation::Movie Recommendation::movieSelect(vector<string> genres, double rating) {
        //Create empty movie vector
        vector<Recommendation::Movie> relevantMovies;
        //genre count check to make sure movie matches respective genres
        int genre_count_check = genres.size();
        //Loop through movieList and add to rating close to list
        for (auto& mov : moviesList) {
            //Check if has matching genres(split by space etc)
            string mov_genres = mov.genres;
            string delimiter = " ";
            size_t pos = 0;
            //genre count to match genre_count_check
            int genre_count = 0;
            for (auto& genre : genres){
                while ((pos = mov_genres.find(delimiter)) != string::npos) {
                    //Check if genre count matches genre_count_check
                    if (genre_count == genre_count_check) break;
                    //Get current genre word
                    string mov_genre = mov_genres.substr(0, pos); 
                    mov_genres.erase(0, pos + delimiter.length());
                    //Check genre and update genre count
                    if (mov_genre == genre) genre_count++;

                    //Account for "ScienceFiction" bs
                    if (mov_genre == "ScienceFiction" && genre == "Sci-Fi") genre_count++;
                }
            }
            //If movie meets genre count, if not move on
            if (genre_count != genre_count_check) {
                continue;
            }
            else {
                //If rating == rating: add to start of list
                double mov_rating = stod(mov.rating);
                if (mov_rating == rating) {
                    relevantMovies.insert(relevantMovies.begin(), mov);
                }
                //If rating += 0.5 rating, add to back of list
                else if (mov_rating >= (rating - 0.5) || mov_rating <= (rating + 0.5)) {
                    relevantMovies.push_back(mov);
                }
            }
        }
        //Return first movie in relevantMovies
        return relevantMovies[0]; 

    }

    Recommendation::Movie Recommendation::randomMovieSelect() {
        //shuffle movieList
        shuffle(moviesList.begin(), moviesList.end(), default_random_engine());

        //Return first index of shuffled list
        return moviesList[0];
    }

    Recommendation::Food Recommendation::randomFoodSelect() {
        Recommendation::Food food; //Return empty struct for now

        return food;
    }
}

