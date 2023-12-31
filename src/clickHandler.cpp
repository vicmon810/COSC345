#include "clickHandler.h"

namespace cosc345
{

    void clickHandler::pop_food(QString genres, Recommendation rec)
    {

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

        // Give food recommendation
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
        bool isChar = false;
        while (startPos < holder.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                isChar = true;
                endPos = startPos + maxCharsPerLine;
            }
            if (!isChar)
                // Append the substring to the result string with a newline character
                resultString += holder.substr(startPos, endPos - startPos) + "\n";
            else
                resultString += holder.substr(startPos, endPos - startPos);
            // Update the starting position for the next iteration
            if (!isChar)
                startPos = endPos + 1;
            else
                startPos = endPos;
        }

        directions = QString::fromStdString(resultString);

        QString ingredients;
        string holder2 = food.ingredients;
        string resultString2;

        startPos = 0;
        isChar = false;
        while (startPos < holder2.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder2.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                isChar = true; 
                endPos = startPos + maxCharsPerLine; 
            }
            if (!isChar)
                // Append the substring to the result string with a newline character
                resultString2 += holder2.substr(startPos, endPos - startPos) + "\n";
            else
                resultString2 += holder2.substr(startPos, endPos - startPos);
            // Update the starting position for the next iteration
            if (!isChar)
                startPos = endPos + 1; 
            else
                startPos = endPos;
        }
        ingredients = QString::fromStdString(resultString2);

        // Dietary requirements
        QString dietary = QString::fromStdString(food.dietary);

        // Create a custom dialog to show the food details
        QDialog dialog;
        QVBoxLayout *layout = new QVBoxLayout;
        QPushButton *titleButton = new QPushButton(("REFRESH FOOD PAIRING"));

        // Display the full food details in QLabel
        QLabel *titleLabel = new QLabel();
        titleLabel->setObjectName("movieTitle"); // To use same qss settings
        titleLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        QLabel *ingredientsLabel = new QLabel();
        ingredientsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        QLabel *directionsLabel = new QLabel();
        directionsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        QLabel *dietaryLabel = new QLabel();
        dietaryLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        titleLabel->setText(title);
        ingredientsLabel->setText("Ingredients: " + ingredients);
        directionsLabel->setText("Directions: " + directions);
        dietaryLabel->setText("Dietary tags:\n" + dietary);

        layout->addWidget(titleLabel);
        layout->addWidget(ingredientsLabel);
        layout->addWidget(directionsLabel);
        layout->addWidget(dietaryLabel);
        layout->addWidget(titleButton);

        QObject::connect(titleButton, &QPushButton::clicked, [&]()
                         {   
                dialog.close();
                clickHandler::pop_food(genres, rec); });

        dialog.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
        dialog.setLayout(layout);
        dialog.setWindowTitle("Food Details");
        dialog.exec();
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
        titleLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *genresLabel = new QLabel();
        genresLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *IMDBLabel = new QLabel();
        IMDBLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *overviewLabel = new QLabel();
        overviewLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *RunTimeLabel = new QLabel();
        RunTimeLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *RatingLabel = new QLabel();
        RatingLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QLabel *RelatesLabel = new QLabel();
        RelatesLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        titleLabel->setText(title);
        genresLabel->setText("Genres: " + genres);
        IMDBLabel->setText("IMDB Number: " + IMDB);
        RunTimeLabel->setText("Run time : " + runtime + " minutes");

        // Convert the rating QString to a double
        double ratingValue = rating.toDouble();

        // Round the rating to 2 decimal places
        ratingValue = qRound(ratingValue * 100) / 100.0;

        // Convert the rounded rating back to a QString
        QString roundedRating = QString::number(ratingValue, 'f', 2);

        // Set the rounded rating in the QLabel
        RatingLabel->setText("Rating: " + roundedRating + "/5");
        RelatesLabel->setText("Release date: " + release);
        int maxDisplayLen = 25;
        if (overview.length() > maxDisplayLen)
        {
            overview += '\n';
            // overview += "...";
        }
        // Test code to fix line bug NEED TO FIX WORDSPLIT BUG
        string holder = overview.toStdString();
        const int maxCharsPerLine = 30;
        string resultString;
        size_t startPos = 0;
        bool isChar = false;
        while (startPos < holder.length())
        {
            // Find the position of the next space within the limit
            size_t endPos = holder.find(' ', startPos + maxCharsPerLine);

            // If no space is found, break the line at the maximum characters
            if (endPos == string::npos)
            {
                isChar = true;
                endPos = startPos + maxCharsPerLine;
            }
            if (!isChar)
                // Append the substring to the result string with a newline character
                resultString += holder.substr(startPos, endPos - startPos) + "\n";
            else
                resultString += holder.substr(startPos, endPos - startPos);
            // Update the starting position for the next iteration
            if (!isChar)
                startPos = endPos + 1;
            else
                startPos = endPos;
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

        dialog.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
        dialog.setLayout(layout);
        dialog.setWindowTitle("Movie Details");
        dialog.exec();
    }
}