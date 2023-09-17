#include "../src/clickImage.h"
#include <iostream>
#include <QApplication>
#include <QMouseEvent>
bool clickableLabelMousePressEventTest()
{
    QWidget *parentWidget = new QWidget();
    ClickableLabel clickableLabel(parentWidget);

    bool signalEmitted = false;
    QObject::connect(&clickableLabel, &ClickableLabel::clicked, [&signalEmitted]()
                     { signalEmitted = true; });

    // Simulate a mouse click event on the clickableLabel
    QMouseEvent *mouseEvent = new QMouseEvent(
        QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(&clickableLabel, mouseEvent);

    // Check if the signal was emitted
    if (signalEmitted)
    {
        std::cout << "ClickableLabel mousePressEvent test passed." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "ClickableLabel mousePressEvent test failed." << std::endl;
        return false;
    }
}

int main()
{
    bool allTestsPassed = true;

    // Run individual test cases and update the allTestsPassed flag
    allTestsPassed &= clickableLabelMousePressEventTest();

    // Print overall test results
    if (allTestsPassed)
    {
        std::cout << "All tests passed." << std::endl;
    }
    else
    {
        std::cerr << "Some tests failed." << std::endl;
    }

    return allTestsPassed ? 0 : 1;
}
