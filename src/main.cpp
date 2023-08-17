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
#include <iostream> //test, delete after use
#include <QDebug>
#include "../include/Connection.h"
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMenu *menu = new QMenu();
    menu->setTitle(QObject::tr("Movie and Food"));
    menu->addAction(QObject::tr("I Feel Lucky"));
    menu->addAction(QObject::tr("Open"));
    menu->addAction(QObject::tr("Save"));
    QMenu *submenu = menu->addMenu(QObject::tr("Settings"));
    submenu->addAction(QObject::tr("Preferences"));
    submenu->addAction(QObject::tr("Language"));

    QFrame frame;
    QPushButton button("Click Me");
    QVBoxLayout *layout_v = new QVBoxLayout;
    QCheckBox *checkBox = new QCheckBox();
    QLineEdit *lineEdit = new QLineEdit();

    checkBox->setText("Movie Size: 10"); // You can replace "10" with the actual movie size
    checkBox->setChecked(true);

    lineEdit->setText("Receipt Size: 20"); // You can replace "20" with the actual receipt size
    lineEdit->setReadOnly(true);

    cosc345::Connection conn;
    conn.est_conn();
    vector<cosc345::Connection::Movies> movies = conn.getDetailMovie();

    QTableWidget *tableWidget = new QTableWidget();
    QStringList headers = {"Genres", "IMDB ID", "Overview", "Release Date", "Runtime", "Title", "Rating", "Food"};
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    int db_size = conn.getSizeMovie();
    tableWidget->setRowCount(db_size);

    for (int row = 0; row < db_size; ++row)
    {
        const cosc345::Connection::Movies &movie = movies[row];
        QTableWidgetItem *genresItem = new QTableWidgetItem(QString::fromStdString(movie.genres));
        QTableWidgetItem *imdbItem = new QTableWidgetItem(QString::fromStdString(movie.imdb_id));
        QTableWidgetItem *overviewItem = new QTableWidgetItem(QString::fromStdString(movie.overview));
        QTableWidgetItem *dateItem = new QTableWidgetItem(QString::number(movie.release_date));
        QTableWidgetItem *runtimeItem = new QTableWidgetItem(QString::number(movie.runtime));
        QTableWidgetItem *titleItem = new QTableWidgetItem(QString::fromStdString(movie.title));
        QTableWidgetItem *ratingItem = new QTableWidgetItem(QString::number(movie.rating));
        QTableWidgetItem *foodItem = new QTableWidgetItem("Popcorn");
        tableWidget->setItem(row, 0, genresItem);
        tableWidget->setItem(row, 1, imdbItem);
        tableWidget->setItem(row, 2, overviewItem);
        tableWidget->setItem(row, 3, dateItem);
        tableWidget->setItem(row, 4, runtimeItem);
        tableWidget->setItem(row, 5, titleItem);
        tableWidget->setItem(row, 6, ratingItem);
        tableWidget->setItem(row, 7, foodItem);
        // ... (set other items)
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(menu);
    // layout->addWidget(button);
    layout->addWidget(tableWidget); // Add the QTableWidget to the layout
    layout->addLayout(layout_v);
    layout_v->addWidget(checkBox);
    layout_v->addWidget(lineEdit);

    frame.setLayout(layout);
    frame.show();

    return app.exec();
}
