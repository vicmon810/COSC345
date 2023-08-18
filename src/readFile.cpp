#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector> // Include the vector header

struct Movies
{
    std::string genres;
    std::string imdb_id;
    std::string overview;
    std::string release_date;
    std::string runtime;
    std::string title;
    std::string rating;
    std::string poster;
};

int main()
{
    std::ifstream inputFile("movies.csv");
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<Movies> moviesDetail; // Declare a vector to store movies

    std::string line;
    while (getline(inputFile, line))
    {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }

        if (!fields.empty())
        {
            std::cout << fields[0] << std::endl;
            // Movies movie;
            // movie.genres = fields[0];
            // movie.poster = fields[1];
            // movie.imdb_id = fields[2];
            // movie.overview = fields[3];
            // movie.rating = fields[4];
            // movie.release_date = fields[5];
            // movie.runtime = fields[6];
            // movie.title = fields[7];

            // moviesDetail.push_back(movie); // Store the movie in the vector
        }
    }

    inputFile.close();

    // Now you have all the movies stored in the "moviesDetail" vector

    return 0;
}
