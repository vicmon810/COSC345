#include "Recommendation.h"

/**
 * Functions for movie and food recommendation
 */
namespace cosc345
{
    // Default constructor
    Recommendation::Recommendation() {}

    Recommendation::Recommendation(vector<Connection::Movies> moviesList, vector<Connection::Food> foodList)
    {
        // Add to vector
        this->moviesList = moviesList;

        // Do it for food as well
        for (auto &f00d : foodList)
        {
            // Initialise food
            Connection::Food food;
            // Transfer data into food
            food.title = f00d.title;
            food.directions = f00d.directions;
            food.ingredients = f00d.ingredients;
            food.NER = f00d.NER;
            food.food_type = f00d.food_type;
            // Append to either sweet or savoury food list
            if (food.food_type == "Savoury")
            {
                cout << "testign" << endl;
                this->savouryFoodList.push_back(food);
            }
            else if (food.food_type == "Sweet")
            {
                cout << "TESTING" << endl;
                this->sweetFoodList.push_back(food);
            }
        }
    }

    vector<string> Recommendation::getGenres() const
    {
        return this->genres;
    }

    // Connection::Movies Recommendation::movieSelect(vector<string> genres, double rating)
    // {

    //     // Create empty movie vector
    //     vector<Connection::Movies> relevantMovies;
    //     // genre count check to make sure movie matches respective genres
    //     int genre_count_check = genres.size();
    //     // Loop through movieList and add to rating close to list
    //     for (auto &mov : moviesList)
    //     {
    //         // Check if has matching genres(split by space etc)
    //         string mov_genres = mov.genres;
    //         string delimiter = " ";
    //         size_t pos = 0;
    //         // genre count to match genre_count_check
    //         int genre_count = 0;
    //         for (auto &genre : genres)
    //         {
    //             while ((pos = mov_genres.find(delimiter)) != string::npos)
    //             {
    //                 // Check if genre count matches genre_count_check
    //                 if (genre_count == genre_count_check)
    //                     break;
    //                 // Get current genre word
    //                 string mov_genre = mov_genres.substr(0, pos);
    //                 mov_genres.erase(0, pos + delimiter.length());
    //                 // Check genre and update genre count
    //                 if (mov_genre == genre)
    //                     genre_count++;

    //                 // Account for "ScienceFiction" bs
    //                 if (mov_genre == "ScienceFiction" && genre == "Sci-Fi")
    //                     genre_count++;
    //             }
    //         }
    //         // If movie meets genre count, if not move on
    //         if (genre_count != genre_count_check)
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             // If rating == rating: add to start of list
    //             double mov_rating = stod(mov.rating);
    //             if (mov_rating == rating)
    //             {
    //                 relevantMovies.insert(relevantMovies.begin(), mov);
    //             }
    //             // If rating += 0.5 rating, add to back of list
    //             else if (mov_rating >= (rating - 0.5) || mov_rating <= (rating + 0.5))
    //             {
    //                 relevantMovies.push_back(mov);
    //             }
    //         }
    //     }
    //     // Return first movie in relevantMovies
    //     return relevantMovies[0];
    // }

    Connection::Movies Recommendation::randomMovieSelect()
    {
        // shuffle movieList
        shuffle(moviesList.begin(), moviesList.end(), default_random_engine());

        // Return first index of shuffled list
        return moviesList[0];
    }

    Connection::Food Recommendation::savouryFoodSelect()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, savouryFoodList.size());
        // shuffle savouryFoodList
        // shuffle(savouryFoodList.begin(), savouryFoodList.end(), default_random_engine());

        // Return first index of shuffled list
        return savouryFoodList[distribution(generator)];
    }

    Connection::Food Recommendation::sweetFoodSelect()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, sweetFoodList.size());
        // shuffle sweetFoodList
        // shuffle(sweetFoodList.begin(), sweetFoodList.end(), default_random_engine());

        // Return first index of shuffled list
        return sweetFoodList[distribution(generator)];
    }
}
