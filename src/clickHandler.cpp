#include "clickHandler.h"

namespace cosc345
{

    void clickHandler::pop_food()
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Message");

        // Use HTML to set a bigger font size for the message
        QString message1 = "<font size='5'>Monster Drink!!!</font>";
        QString message2 = "<font size='5'>Pop Corn!!!</font> ";
        QString message3 = "<font size='5'>Ice Cream</font>";
        QString message4 = "<font size='5'>Ice </font>";
        std::srand(std::time(nullptr));

        // Generate a random number from 0 to 3 to select the RNG
        int rngChoice = std::rand() % 4;
        qDebug() << rngChoice;

        // Depending on the value of rngChoice, select the RNG
        switch (rngChoice)
        {
        case 0:
            msgBox.setText(message1);
            break;
        case 1:
            msgBox.setText(message2);
            break;
        case 2:
            msgBox.setText(message3);
            break;
        case 3:
            msgBox.setText(message4);
            break;
        }

        msgBox.exec();
    }

    void clickHandler::handleItemClicked(QString title, QString genres, QString IMDB, QString overview, QString runtime, QString rating, QString release)
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
                         { clickHandler::pop_food(); });

        dialog.setLayout(layout);
        dialog.setWindowTitle("Movie Details");
        dialog.exec();
    }
}
