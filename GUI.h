#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <QObject>
#include <QPushButton>

namespace cosc345
{
    class GUI : public QObject
    {
        Q_OBJECT
    public:
        GUI();
        virtual ~GUI();               // Added virtual destructor
        virtual void dummyFunction(); // Added a dummy virtual member function

    public slots:
        void buttonClicked();

    private:
        QPushButton *button;
    };
}

#endif // GUI_H_INCLUDED
