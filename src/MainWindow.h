#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QDebug>
#include <QCheckBox>
#include <QMessageBox>
#include "Recommendation.h"
#include "connection.h"
#include "clickImage.h"
#include "clickHandler.h"
using namespace cosc345;
using namespace std;
/*!
 * @class MainWindow
 * @brief The main window class for the Movie and Food application.
 *
 * This class represents the main window of the Movie and Food application.
 * It provides a user interface for searching and displaying movie posters.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the MainWindow class.
     *
     * @param parent The parent widget (if any).
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

private slots:
    /*!
     * @brief Slot function to handle the search operation.
     */
    void handleSearch();

    /*!
     * @brief Slot function to handle the navigation to the previous page.
     */
    void handlePageNumberPrev();

    /*!
     * @brief Slot function to handle the navigation to the next page.
     */
    void handlePageNumberNext();
    /*!
     * @brief Slot fuction to return home page
     */
    void handleHome();
    /*!
     * @brief Slot function for re-shuffle current item
     */
    void handleShuffle();

private:
    QGridLayout *gridLayout; /**< Grid layout for displaying movie posters. */
    QVBoxLayout *menuAndSearchLayout;
    QLineEdit *searchBar;      /**< Text input for searching movies. */
    QPushButton *pageNum1;         /**< Button for navigating to the previous page. */
    QPushButton *pageNum2;         /**< Button for navigating to the next page. */
    QScrollBar *verticalScrollBar; /**< Vertical scrollbar for the poster grid. */
    // Define a QLabel for page numbers
    QLabel *pageNumberLabel;
    int page1 = 1;       /**< Current page number. */
    int page2 = 2;       /**< Next page number. */
    int maxPerPage = 30; /**< Maximum number of posters per page. */
    int pages;
    int remain;
    bool pageCheck = false;                           /**< Flag for page number change. */
    string defaultText = "";                          /**< Default search text. */
    cosc345 ::Recommendation rec;                     /**< Recommendation engine. */
    cosc345 ::Connection conn;                        /**< Database connection. */
    vector<cosc345::Connection::Movies> searchResult; /**< Results of the movie search. */
    vector<cosc345::Connection::Movies> movies;       /**< List of movies. */
    vector<cosc345::Connection::Food> foods;          /**< List of foods. */
    vector<cosc345::Connection::Movies> homeList;     /**< List of movies use for default home button. */
    vector<cosc345::Connection::Movies> tempResult;   /**< List of movies use for shuffle. */
    /*!
     * @brief Initialize the backend components of the application.
     *        (Database connection, movie and food data)
     */
    void backendInit();

    /*!
     * @brief Set up the user interface elements and layout.
     */
    void setupUI();

    /*!
     * @brief Display movie posters on the grid layout.
     *
     * @param movies The list of movies to display.
     * @param gridLayout The grid layout where posters are displayed.
     * @param rec The recommendation engine for handling poster clicks.
     */
    void displayPosters(vector<cosc345::Connection::Movies> movies);

    /*!
     * @brief Clear all posters from the grid layout.
     */
    void clearPosters();
};
