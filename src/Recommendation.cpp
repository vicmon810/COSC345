#include "Recommendation.h"

/**
 * Functions for movie and food recommendation
 */
namespace cosc345
{
    // Default constructor
    Recommendation::Recommendation() {}

    Recommendation::Recommendation(const vector<Connection::Movies> moviesList, const vector<Connection::Food> foodList)
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
            food.dietary = f00d.dietary;
            // Append to either sweet or savoury food list
            if (food.food_type == "Savoury")
            {
                this->savouryFoodList.push_back(food);
            }
            else if (food.food_type == "Sweet")
            {
                this->sweetFoodList.push_back(food);
            }
        }
    }

    vector<string> Recommendation::getGenres() const
    {
        return this->genres;
    }

    Connection::Movies Recommendation::randomMovieSelect()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed); 
        // shuffle movieList
        uniform_int_distribution<int> distribution(0, moviesList.size());

        // Return first index of shuffled list
        return moviesList[distribution(generator)];
    }

    Connection::Food Recommendation::savouryFoodSelect()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, savouryFoodList.size() - 1);

        // Return first index of shuffled list
        return savouryFoodList[distribution(generator)];
    }

    Connection::Food Recommendation::sweetFoodSelect()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        // Randomiser
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, sweetFoodList.size() - 1);

        // Return first index of shuffled list
        return sweetFoodList[distribution(generator)];
    }
}
