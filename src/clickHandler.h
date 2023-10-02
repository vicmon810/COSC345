#ifndef CLICK_HANDLER_H
#define CLICK_HANDLER_H
#include <QApplication>
#include <QPushButton>
#include <QMenu>
#include <QObject>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThreadPool>
#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QFile>
#include <QPixmap>
#include <QMenuBar>
#include <QString>
#include <random>
#include <QWidgetAction>
#include "Recommendation.h"

namespace cosc345
{
    /*!
     * @brief The clickHandler class handles click events and provides related functionality.
     *
     * It can handle click events on movie items and perform actions such as displaying food recommendations.
     */
    class clickHandler
    {
    private:
        public:
        /*!
         * @brief This private function generates and displays food recommendations based on movie genres.
         * @param genres The genres of the selected movie.
         * @param rec An instance of the Recommendation class for recommendation data.
         */
        void pop_food(QString genres, Recommendation rec);
        /*!
         * @brief Handles the click event on a movie item.
         *
         * This function is called when a movie item is clicked and can perform actions based on the clicked item's data.
         * @param title The title of the clicked movie.
         * @param genres The genres of the clicked movie.
         * @param IMDB The IMDB ID of the clicked movie.
         * @param overview A brief overview of the clicked movie.
         * @param runtime The runtime of the clicked movie.
         * @param rating The rating of the clicked movie.
         * @param release The release date of the clicked movie.
         * @param rec An instance of the Recommendation class for recommendation data.
         */
        void handleItemClicked(QString title, QString genres, QString IMDB, QString overview, QString runtime, QString rating, QString release, Recommendation rec);
    };
}
#endif // CLICK_HANDLER_H