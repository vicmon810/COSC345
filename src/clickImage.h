#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QDebug>
/*!
 * @file ClickableLabel.h
 * Header file for the ClickableLabel.cpp
 */

/*!
 * @class ClickableLabel
 * @brief Represents a custom clickable label widget that emits a signal when clicked.
 *
 * This class inherits from QLabel and adds the ability to emit a custom "clicked" signal
 * when the label is clicked.
 */
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    /*!
     * @brief Constructs a ClickableLabel instance.
     * @param parent The parent QWidget.
     * @param f Window flags for the label.
     */
    explicit ClickableLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /*!
     * @brief Destructor for ClickableLabel.
     */
    ~ClickableLabel();

signals:
    /*!
     * @brief Signal emitted when the label is clicked.
     *
     * This signal is emitted when the user clicks on the label.
     */
    void clicked();

protected:
    /*!
     * @brief Handles mouse press events for the label.
     * @param event The mouse press event.
     *
     * This function is called when the user presses the mouse button over the label.
     * It emits the "clicked" signal to notify connected slots.
     */
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H