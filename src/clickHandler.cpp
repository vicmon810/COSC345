#include "clickHandler.h"

namespace cosc345
{

    void clickHandler::pop_food(QString genres, Recommendation rec)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Food Recommendation");

        // Set savoury genres (why is it here? Lmao idgaf)
        vector<string> savouryGenres = {"Action", "Adventure",
                                        "Crime", "Drama",
                                        "Horror", "Thriller",
                                        "War", "Documentary", "Mystery"};

        // Qstring to split string whatever thing
        string tempGenres = genres.toStdString();
        // get vector of genres
        vector<string> movieGenres;
        string temp;
        stringstream ss(tempGenres);

        while (getline(ss, temp, ' '))
        {
            movieGenres.push_back(temp);
        }

        // Boolean check to be used
        bool check = false;
        // Loop through genres and check if its in savoury genres, if one is satisfied recommend savoury food
        for (auto &genre : movieGenres)
        {
            if (check)
                break;
            for (auto &savouryGenre : savouryGenres)
            {
                if (genre == savouryGenre)
                {
                    check = true;
                    break;
                }
            }
        }

        // Give savoury food recommendation
        Connection::Food food;
        if (check)
        {
            food = rec.savouryFoodSelect();
        }
        else
        {
            food = rec.sweetFoodSelect();
        }
        // Get message components
        QString title = QString::fromStdString(food.title);
        QString type = QString::fromStdString(food.food_type);

        QString directions;
        string holder = food.directions;
        const int maxCharsPerLine = 30;
        string resultString;
        size_t startPos = 0;

        while (startPos < holder.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                endPos = startPos + maxCharsPerLine;
            }

            // Append the substring to the result string with a newline character
            resultString += holder.substr(startPos, endPos - startPos) + "\n";

            // Update the starting position for the next iteration
            startPos = endPos + 1;
        }

        directions = QString::fromStdString(resultString);

        QString ingredients;
        string holder2 = food.ingredients;
        string resultString2;

        startPos = 0;

        while (startPos < holder2.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder2.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                endPos = startPos + maxCharsPerLine;
            }

            // Append the substring to the result string with a newline character
            resultString2 += holder2.substr(startPos, endPos - startPos) + "\n";

            // Update the starting position for the next iteration
            startPos = endPos + 1;
        }
        ingredients = QString::fromStdString(resultString2);

        msgBox.setText("Title: " + title + "\n" + "\n" + "Ingredients: " + ingredients + "\n" + "Directions: " + directions); // Noob way lmao
        msgBox.exec();
    }

    void clickHandler::handleItemClicked(QString title, QString genres, QString IMDB, QString overview, QString runtime, QString rating, QString release, Recommendation rec)
    {
        // Get the text (movie details) from the clicked item
        // QString movieDetails = item->text(QString title);

        // Create a custom dialog to show the full movie details
        QDialog dialog;
        QVBoxLayout *layout = new QVBoxLayout;
        QPushButton *titleButton = new QPushButton(("FOOD PAIRING"));
        // Display the full movie details in QLabel
        QLabel *titleLabel = new QLabel();
        titleLabel->setObjectName("movieTitle");
        QLabel *genresLabel = new QLabel();
        QLabel *IMDBLabel = new QLabel();
        QLabel *overviewLabel = new QLabel();
        QLabel *RunTimeLabel = new QLabel();
        QLabel *RatingLabel = new QLabel();
        QLabel *RelatesLabel = new QLabel();
        titleLabel->setText("Title: " + title);
        genresLabel->setText("Genres: " + genres);
        IMDBLabel->setText("IMDB Number: " + IMDB);
        RunTimeLabel->setText("Run time : " + runtime + " mints");
        RatingLabel->setText("Rating: " + rating + "/5");
        RelatesLabel->setText("Release date: " + release);
        int maxDisplayLen = 25;
        if (overview.length() > maxDisplayLen)
        {
            overview += '\n';
            // overview += "...";
        }
        // Test code to fix line bug
        string holder = overview.toStdString();
        const int maxCharsPerLine = 30;
        string resultString;
        size_t startPos = 0;

        while (startPos < holder.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                endPos = startPos + maxCharsPerLine;
            }

            // Append the substring to the result string with a newline character
            resultString += holder.substr(startPos, endPos - startPos) + "\n";

            // Update the starting position for the next iteration
            startPos = endPos + 1;
        }
        overview = QString::fromStdString(resultString);
        overviewLabel->setText("Overview: " + overview);
        layout->addWidget(titleLabel);
        layout->addWidget(genresLabel);
        layout->addWidget(IMDBLabel);
        layout->addWidget(overviewLabel);
        layout->addWidget(RelatesLabel);
        layout->addWidget(RatingLabel);
        layout->addWidget(RunTimeLabel);
        layout->addWidget(titleButton);

        QObject::connect(titleButton, &QPushButton::clicked, [&]()
                         { clickHandler::pop_food(genres, rec); });

        dialog.setLayout(layout);
        dialog.setWindowTitle("Movie Details");
        dialog.exec();
    }
}
