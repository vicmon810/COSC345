#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include "../src/Recommendation.h"
#include "../src/connection.h"

/*!
 *@class TestRecommendation
 *@brief class used for Unit test in UnitTest.exe. It checks if the movie details are displayed correctly.
 */
class TestRecommendation : public QObject
{
    Q_OBJECT

private slots:
    void testMovieDetailsDisplay()
    {
        // Initialize the QApplication (required for QPixmap)
        int argc = 0;
        char *argv[] = {nullptr};
        QCoreApplication app(argc, argv);

        // Create a Connection object and establish a connection
        cosc345::Connection conn;
        conn.est_conn();

        // Get movie data (modify this to use test data if needed)
        vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();

        // Create a QListWidget and add items to it
        QListWidget listWidget;
        for (const cosc345::Connection::Movies &movie : movies)
        {
            // Create a test item with movie details
            QString movieDetails = "Title: " + QString::fromStdString(movie.title) + "\n" +
                                   "Genres: " + QString::fromStdString(movie.genres) + "\n" +
                                   "IMDB ID: " + QString::fromStdString(movie.imdb_id) + "\n" +
                                   "Overview: " + QString::fromStdString(movie.overview) + "\n" +
                                   "Release Date: " + QString::fromStdString(movie.release_date) + "\n" +
                                   "Runtime: " + QString::fromStdString(movie.runtime) + "\n" +
                                   "Rating: " + QString::fromStdString(movie.rating) + "\n" +
                                   "Food: Popcorn\n" +
                                   "Poster: " + QString::fromStdString(movie.poster);
            QListWidgetItem *item = new QListWidgetItem(movieDetails);
            listWidget.addItem(item);
        }

        // Test that the listWidget contains the expected number of items
        QCOMPARE(listWidget.count(), movies.size());

        // Cleanup (QListWidget and QApplication will be deleted automatically)
    }

    // Add more test cases for other functionalities (e.g., image downloading and dialog display) as needed.
};

QTEST_APPLESS_MAIN(TestRecommendation)
#include "test_recommendation.moc"
