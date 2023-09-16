#ifndef MOVIE_APP_FUNCTIONS_H
#define MOVIE_APP_FUNCTIONS_H

#include <QString>
#include <QPixmap>
#include <vector>
#include <QLabel>
#include "clickImage.h" // Include any necessary headers for ClickableLabel and other custom classes

class ImageDownloadWorker;

QPixmap downloadImage(const QString &imageUrl);
void displayPoster(std::vector<cosc345::Connection::Movies> posters, QGridLayout *gridLayout);
std::vector<cosc345::Connection::Movies> getAllMovie();
int getAllSize();
int window(int argc, char **argv);

#endif // MOVIE_APP_FUNCTIONS_H
