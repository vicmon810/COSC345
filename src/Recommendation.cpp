#include "Recommendation.h"

/**
 * Functions for movie and food recommendation
 */
namespace cosc345
{
    // Default constructor
    Recommendation::Recommendation() {}

<<<<<<< HEAD
    Recommendation::Recommendation(Connection conn)
    {
        // Add to vector
        vector<Connection::Movies> movies = conn.getDetailMovie();
        vector<Connection::Food> foods = conn.getDetailFood();

        // Transfer Connection::Movies to Recommendation::Movie since they are from
        // different classes. So I dont have to use Connection:: Connection:: Connection::
        // for everything I do in recommendation.cpp. Also the recommendation functions
        // cant really return a Connection:: item in a Recommendation:: function, C++ is ass
        for (const cosc345::Connection::Movies &mov : movies)
        {
            // Initialise movie
            Recommendation::Movie movie;
            // Transfer data into movie
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

        // Do it for food as well
        for (const cosc345::Connection::Food &f00d : foods)
        {
            // Initialise food
            Recommendation::Food food;
            // Transfer data into food
=======
    Recommendation::Recommendation(vector<Connection::Movies> moviesList, vector<Connection::Food> foodList) {
        //Add to vector
        this->moviesList = moviesList; 

        //Do it for food as well
        for (const cosc345::Connection::Food& f00d : foodList)
        {
            //Initialise food
            Connection::Food food;
            //Transfer data into food
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657
            food.title = f00d.title;
            food.directions = f00d.directions;
            food.ingredients = f00d.ingredients;
            food.NER = f00d.NER;
            food.food_type = f00d.food_type;

            // Append to either sweet or savoury food list
            if (food.food_type == "Savory")
            {
                savouryFoodList.push_back(food);
            }
            else if (food.food_type == "Sweet")
            {
                sweetFoodList.push_back(food);
            }
        }
    }

    vector<string> Recommendation::getGenres() const
    {
        return this->genres;
    }

<<<<<<< HEAD
    Recommendation::Movie Recommendation::movieSelect(vector<string> genres, double rating)
    {
        // Create empty movie vector
        vector<Recommendation::Movie> relevantMovies;
        // genre count check to make sure movie matches respective genres
=======
    Connection::Movies Recommendation::movieSelect(vector<string> genres, double rating) {
        //Create empty movie vector
        vector<Connection::Movies> relevantMovies;
        //genre count check to make sure movie matches respective genres
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657
        int genre_count_check = genres.size();
        // Loop through movieList and add to rating close to list
        for (auto &mov : moviesList)
        {
            // Check if has matching genres(split by space etc)
            string mov_genres = mov.genres;
            string delimiter = " ";
            size_t pos = 0;
            // genre count to match genre_count_check
            int genre_count = 0;
            for (auto &genre : genres)
            {
                while ((pos = mov_genres.find(delimiter)) != string::npos)
                {
                    // Check if genre count matches genre_count_check
                    if (genre_count == genre_count_check)
                        break;
                    // Get current genre word
                    string mov_genre = mov_genres.substr(0, pos);
                    mov_genres.erase(0, pos + delimiter.length());
                    // Check genre and update genre count
                    if (mov_genre == genre)
                        genre_count++;

                    // Account for "ScienceFiction" bs
                    if (mov_genre == "ScienceFiction" && genre == "Sci-Fi")
                        genre_count++;
                }
            }
            // If movie meets genre count, if not move on
            if (genre_count != genre_count_check)
            {
                continue;
            }
            else
            {
                // If rating == rating: add to start of list
                double mov_rating = stod(mov.rating);
                if (mov_rating == rating)
                {
                    relevantMovies.insert(relevantMovies.begin(), mov);
                }
                // If rating += 0.5 rating, add to back of list
                else if (mov_rating >= (rating - 0.5) || mov_rating <= (rating + 0.5))
                {
                    relevantMovies.push_back(mov);
                }
            }
        }
        // Return first movie in relevantMovies
        return relevantMovies[0];
    }

<<<<<<< HEAD
    Recommendation::Movie Recommendation::randomMovieSelect()
    {
        // shuffle movieList
=======
    Connection::Movies Recommendation::randomMovieSelect() {
        //shuffle movieList
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657
        shuffle(moviesList.begin(), moviesList.end(), default_random_engine());

        // Return first index of shuffled list
        return moviesList[0];
    }

<<<<<<< HEAD
    Recommendation::Food Recommendation::savouryFoodSelect(vector<Food> foodlist)
    {
        // shuffle savouryFoodList
=======
    Connection::Food Recommendation::savouryFoodSelect() {
        //shuffle savouryFoodList
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657
        shuffle(savouryFoodList.begin(), savouryFoodList.end(), default_random_engine());

        // Return first index of shuffled list
        return savouryFoodList[0];
    }

<<<<<<< HEAD
    Recommendation::Food Recommendation::sweetFoodSelect(vector<Food> foodlist)
    {
        // shuffle sweetFoodList
=======
    Connection::Food Recommendation::sweetFoodSelect() {
        //shuffle sweetFoodList
>>>>>>> 320d0b371b010dea09e3ef26217be3785200e657
        shuffle(sweetFoodList.begin(), sweetFoodList.end(), default_random_engine());

        // Return first index of shuffled list
        return sweetFoodList[0];
    }
}
