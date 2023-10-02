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
#include <QMessageBox>
#include "Recommendation.h"
#include "connection.h"
#include "clickImage.h"
#include "clickHandler.h"
using namespace cosc345;
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSearch();
    void handlePageNumber1();
    void handlePageNumber2();

    // Add more slots as needed

private:
    QGridLayout *gridLayout;
    QLineEdit *searchBar;
    QPushButton *pageNum1;
    QPushButton *pageNum2;
    int page1 = 1;
    int page2 = 2;
    int maxPerPage = 51;
    bool pageCheck = false;
    string defaultText = "";
    cosc345 ::Recommendation rec;
    cosc345 ::Connection conn;
    vector<cosc345::Connection::Movies> searchResult;
    vector<cosc345::Connection::Movies> movies;
    vector<cosc345::Connection::Food> foods; // Declare the foods vector here
    void backendInit();                      // You can declare this function if needed
    void setupUI();
    void displayPosters(vector<cosc345::Connection::Movies> movies, QGridLayout *gridLayout, Recommendation rec);
    void clearPosters();
};
