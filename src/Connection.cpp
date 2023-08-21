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
        std::ifstream inputFile("Movies.csv");
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
    }

    int Connection::getSizeMovie()
    {
        size_movie = moviesDetail.size();
        return size_movie;
    }

    /**
     * Returns the details of all movies
     */
    vector<Connection::Movies> Connection::getDetailMovie()
    {

        return moviesDetail;
    }

}
