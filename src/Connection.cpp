#include "../include/Connection.h"

/**
 * Functions for connecting to mongodb atlas database
 */
namespace cosc345
{
    Connection::Connection() {}

    /**
     * Connect to MongoDB and get all the data
     */
    void Connection::est_conn()
    {

        std::ifstream inputFile("../data/movies.csv");
        if (!inputFile.is_open())
        {
            std::cerr << "Failed to open the file." << std::endl;
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
            if (fields.size() >= 8) // Make sure you have at least 8 fields
            {
                Movies movie;
                movie.genres = fields[0];
                movie.poster = fields[1];
                movie.imdb_id = fields[2];
                movie.overview = fields[3];
                movie.rating = fields[4];
                movie.release_date = fields[5];
                movie.runtime = fields[6];
                movie.title = fields[7];
                cout << "title: " << fields[7] << endl;
                cout << "------------" << endl;
                cout << "generes: " << fields[0] << endl;
                moviesDetail.push_back(movie); // Assuming you have a vector named moviesDetail
            }
        }
        cout << moviesDetail.size() << endl;
        inputFile.close();
    }

    /*
    @Desc:return total size of the movied data set
    */
    int Connection::getSizeMovie()
    {
        return size_movie;
    }

    /*
    @Desc:return total size of the food in data set
    */
    int Connection::getSizeFood()
    {
        return size_food;
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
}