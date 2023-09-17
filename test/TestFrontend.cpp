// #include "TestFrontend.h"

// class TestClickHandler : public QObject
// {
//     Q_OBJECT

// private slots:
//     void cosc345::testBackend::testPopFood()
//     {
//         // Create a clickHandler instance and a Recommendation instance for testing
//         cosc345::clickHandler handler;
//         cosc345::Recommendation recommendation;

//         // Call the pop_food method with some test data
//         QString genres = "Action Drama";
//         handler.pop_food(genres, recommendation);

//         // Add assertions to check the behavior of the pop_food method
//         // For example, you can check if the message box was shown or if food was recommended correctly.
//         // Replace these assertions with your actual test logic.
//         QVERIFY2(true, "Add your test assertions here");
//     }

//     void cosc345::testBackend::testHandleItemClicked()
//     {
//         // Create a clickHandler instance and a Recommendation instance for testing
//         cosc345::clickHandler handler;
//         cosc345::Recommendation recommendation;

//         // Call the handleItemClicked method with some test data
//         QString title = "Test Movie";
//         QString genres = "Action Drama";
//         QString IMDB = "123456";
//         QString overview = "This is a test overview.";
//         QString runtime = "120 minutes";
//         QString rating = "7.5";
//         QString release = "2023-09-15";

//         // You may need to set up your environment or mock certain behavior to test this method properly.
//         // Replace these function calls with your actual test logic.
//         handler.handleItemClicked(title, genres, IMDB, overview, runtime, rating, release, recommendation);

//         // Add assertions to check the behavior of the handleItemClicked method.
//         // For example, you can check if the dialog was created and if the clickHandler::pop_food method was called.
//         // Replace these assertions with your actual test logic.
//         QVERIFY2(true, "Add your test assertions here");
//     }
// };

// // QTEST_MAIN(TestClickHandler)
// #include "testFrontend.moc"