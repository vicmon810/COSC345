/*!
@file: read movies data from a csv file and pass this data to Qt based GUI
*/
#include "connection.h"

namespace cosc345
{
    Connection::Connection() {}

    /*!
     * @brief: this function do something magic
     */
    void Connection::est_conn()
    {
        //Read Movie Data
        std::ifstream inputFile("Movies.csv");
        if (!inputFile.is_open())
        {
            std::cerr << "Failed to open Movie file." << std::endl;
        }

        std::string line;
        while (getline(inputFile, line))
        {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;
            while (getline(ss, field, ','))
            {
                // cout << "Field: " << field << endl;
                fields.push_back(field);
            }
            int size = fields.size();
            // cout << size << endl;
            // genres	poster  imdb_id	overview rating	release_date	runtime	title
            // 0        1           2       x         x-4         x-3             x-2     x-1
            Movies movie;
            for (int i = 0; i < fields.size(); i++)
            {

                if (i == 0)
                    movie.genres = fields[0];
                if (i == 1)
                    movie.poster = fields[1];
                if (i == 2)
                    movie.imdb_id = fields[2];
                if (i == fields.size() - 1)
                    movie.title = fields[fields.size() - 1];
                if (i == fields.size() - 2)
                    movie.runtime = fields[fields.size() - 2];
                if (i == fields.size() - 3)
                    movie.release_date = fields[fields.size() - 3];
                if (i == fields.size() - 4)
                    movie.rating = fields[fields.size() - 4];
                if (i > 2 && i < fields.size() - 4)
                    movie.overview.append(fields[i]);
            }
            moviesDetail.push_back(movie);
        }

        size_movie = moviesDetail.size();
        inputFile.close();

        //Read Food Data
        ifstream inputFile2("curated.txt");
        if (!inputFile2.is_open())
        {
            cerr << "Failed to open Food file." << endl;
        }
        string line2;
        while (getline(inputFile2, line2))
        {
            vector<string> fields;
            stringstream ss(line2);
            string field;
            while (getline(ss, field, '\t'))
            {   
                fields.push_back(field);
            }
            int size = fields.size();

            Food food;
            for (int i = 0; i < fields.size(); i++)
            {
                //Noob way ahahahaha
                if (i == 0) food.title = fields[0];
                if (i == 1) food.ingredients = fields[1];
                if (i == 2) food.directions = fields[2];
                if (i == 3) food.NER = fields[3];
                if (i == 4) food.food_type = fields[4];
            }
            foodDetail.push_back(food);
        }

        size_food = foodDetail.size();
        inputFile2.close();
    }

    /**
     * Returns the size of the movie detail vector (the total number of movies)
     */
    int Connection::getSizeMovie()
    {
        return moviesDetail.size();
    }

    /**
     * Returns the size of the food detail vector (the total number of food)
     */
    int Connection::getSizeFood()
    {
        return foodDetail.size();
    }

    /**
     * Returns the details of all movies
     */
    vector<Connection::Movies> Connection::getDetailMovie()
    {

        return moviesDetail;
    }

    /**
     * Returns the details of all food
     */
    vector<Connection::Food> Connection::getDetailFood()
    {

        return foodDetail;
    }

    vector<Connection::Movies> Connection::searching(string key)
    {
        Connection::est_conn();

        vector<Connection::Movies>
            totalMovie = Connection::getDetailMovie();

        int sizeMovies = Connection::getSizeMovie();
        cout << sizeMovies << endl;
        for (int i = 0; i < sizeMovies; i++)
        {
            string title = totalMovie[i].title;
            transform(title.begin(), title.end(), title.begin(), ::tolower);
            // if (title == key)
            if (title.find(key) != std::string::npos)
            {
                searchResult.push_back(totalMovie[i]);
                // cout << searchResult[i].title << endl;
            }
        }
        // cout << "search result: " << searchResult[0].title << endl;
        // for (int c = 0; c < searchResult.size(); c++)
        // {
        //     cout << searchResult[c].title << endl;
        // }
        return searchResult;
    }

    vector<Connection::Movies> Connection::sorting(string rating)
    {

        return moviesDetail;
    }
}
