#include <iostream>
#include "../src/clickImage.h"
#define CATCH_CONFIG_MAIN // Include this to let Catch2 generate the main function.
#include <catch2/catch_test_macros.hpp>
#include <QApplication>
#include <QMouseEvent>
TEST_CASE("ClickableLabel mousePressEvent test", "[clickableLabel]")
{
    QWidget parentWidget;
    ClickableLabel clickableLabel(&parentWidget);

    bool signalEmitted = false;
    QObject::connect(&clickableLabel, &ClickableLabel::clicked, [&signalEmitted]()
                     { signalEmitted = true; });

    // Simulate a mouse click event on the clickableLabel
    QMouseEvent *mouseEvent =
        new QMouseEvent(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(&clickableLabel, mouseEvent);

    // Check if the signal was emitted
    REQUIRE(signalEmitted); // Catch2 assertion macro

    std::cout << "ClickableLabel mousePressEvent test passed." << std::endl;
}
