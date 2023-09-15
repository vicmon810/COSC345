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
#include <QFile>
#include <QPixmap>
#include <QMenuBar>
#include <QString>
#include <random>

namespace cosc345
{
    class clickHandler
    {
    private:
        /*!
        *@note: Please delete this after using
        @return: random food from per-set
        */
        void pop_food();

    public:
        /*!
         *@brief: Declaration of handleItemClicked function
         *@param item : QListWidgetItem
         */
        void handleItemClicked(QString title, QString genres, QString IMDB, QString overview, QString runtime, QString rating, QString release);
    };
}