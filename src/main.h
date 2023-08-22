#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "Recommendation.h"
#include "connection.h"
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
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThreadPool>

/*!
 *@brief: Declaration of handleItemClicked function
 *@param item : QListWidgetItem
 */
void handleItemClicked(QListWidgetItem *item);

/*!
 *@brief Declaration of downloadImage function
 *@param imageUrl: QString represents poster resource download link
 *@return poster images
 */
QPixmap downloadImage(const QString &imageUrl);

#endif // MAIN_H_INCLUDED