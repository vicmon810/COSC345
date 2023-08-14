// #include "../include/GUI.h"

// /**
//  * File for GUI things
//  */
// namespace cosc345
// {
//     /**
//      * Default constructor
//      */
//     GUI::GUI()
//     {
//         // Sorry Kris commenting out to test
//         /* button = new QPushButton("Click me!");
//          connect(button, &QPushButton::clicked, this, &GUI::buttonClicked);
//          button->show();*/
//     }

//     /**
//      *  TestConstructor
//      */
//     GUI::GUI(int &argc, char *argv[])
//     { // NEEDS FIXINGGG

//         // Initialise app
//         QApplication app(argc, argv);

//         // Create a QMainWindow
//         QMainWindow mainWindow;

//         // Create a QWidget to hold the main content
//         QWidget *centralWidget = new QWidget(&mainWindow);
//         mainWindow.setCentralWidget(centralWidget);

//         // Add widgets to the main window
//         QVBoxLayout *layout = new QVBoxLayout(centralWidget);
//         QPushButton *button = new QPushButton("Click");
//         layout->addWidget(button);

//         // Step 6: Show the window
//         mainWindow.show();

//         // Step 3: Run the application
//         app.exec();
//     }

//     void GUI::buttonClicked()
//     {
//         qDebug() << "Button clicked!";
//     }

//     GUI::~GUI()
//     {
//         // delete button;
//     }

//     void GUI::dummyFunction() {} // Definition for the dummy virtual member function

// }
