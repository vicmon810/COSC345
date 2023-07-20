#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
* Header file for Connection.cpp
*/
namespace cosc345
{
    class Connection
    {
    public:
        Connection();
        void est_conn();
        int getSizeMovie();
        int getSizeFood();

    private:
        string result;
        int size_movie;
        int size_food;
    };
}

#endif