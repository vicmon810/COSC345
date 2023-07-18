#include "GUI.h"
#include <QDebug>

namespace cosc345
{
    GUI::GUI()
    {
        button = new QPushButton("Click me!");
        connect(button, &QPushButton::clicked, this, &GUI::buttonClicked);
        button->show();
    }

    void GUI::buttonClicked()
    {
        qDebug() << "Button clicked!";
    }
    
    GUI::~GUI()
    {
        delete button;
    }

    void GUI::dummyFunction() {} // Definition for the dummy virtual member function
}
