#include "clickHandler.h"

namespace cosc345
{

    void clickHandler::pop_food(QString genres, Recommendation rec)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Food Details");

        //Set savoury genres (why is it here? Lmao idgaf)
        vector<string> savouryGenres = { "Action", "Adventure",
                                         "Crime", "Drama",
                                         "Horror",  "Thriller",
                                         "War", "Documentary", "Mystery"};

        //Qstring to split string whatever thing
        string tempGenres = genres.toStdString();
        //get vector of genres
        vector<string> movieGenres;
        string temp;
        stringstream ss(tempGenres);

        while (getline(ss, temp, ' ')) {
            movieGenres.push_back(temp);
        }


        //Boolean check to be used
        bool check = false;
        //Loop through genres and check if its in savoury genres, if one is satisfied recommend savoury food
        for (auto& genre : movieGenres) {
            if (check) break;
            for (auto& savouryGenre : savouryGenres) {
                if (genre == savouryGenre) check == true;
                break;
            }
        }
        
        //Give savoury food recommendation
        Connection::Food food;
        QString title;
        QString type;

        if (check) {
            food = rec.savouryFoodSelect();
            title = QString::fromStdString(food.title);
            type = QString::fromStdString(food.food_type);
        }
        else {
            food = rec.sweetFoodSelect();
            title = QString::fromStdString(food.title);
            type = QString::fromStdString(food.food_type);
        }

        msgBox.setText(title + "\n" + type);
        msgBox.exec();
    }

    void clickHandler::handleItemClicked(QString title, QString genres, QString IMDB, QString overview, QString runtime, QString rating, QString release, Recommendation rec)
    {
        // Get the text (movie details) from the clicked item
        // QString movieDetails = item->text(QString title);

        // Create a custom dialog to show the full movie details
        QDialog dialog;
        QVBoxLayout *layout = new QVBoxLayout;
        QPushButton *titleButton = new QPushButton(("Recommending food"));
        // Display the full movie details in QLabel
        QLabel *titleLabel = new QLabel();
        QLabel *genresLabel = new QLabel();
        QLabel *IMDBLabel = new QLabel();
        QLabel *overviewLabel = new QLabel();
        titleLabel->setText("Title: " + title);
        genresLabel->setText("Genres: " + genres);
        IMDBLabel->setText("IMDB Number: " + IMDB);
        int maxDisplayLen = 25;
        if (overview.length() > maxDisplayLen)
        {
            overview.truncate(maxDisplayLen);
            overview += "...";
        }

        overviewLabel->setText("Overview: " + overview);
        layout->addWidget(titleLabel);
        layout->addWidget(genresLabel);
        layout->addWidget(IMDBLabel);
        layout->addWidget(overviewLabel);
        layout->addWidget(titleButton);

        QObject::connect(titleButton, &QPushButton::clicked, [&]()
                         { clickHandler::pop_food(genres, rec); });

        dialog.setLayout(layout);
        dialog.setWindowTitle("Movie Details");
        dialog.exec();
    }
}
