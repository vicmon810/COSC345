#include <iostream>
#include <cassert>
#include "../src/connection.h"
#include "../src/Recommendation.h"
using namespace std;

namespace cosc345
{
    /*!
    @brief: Back_end testing class, using Unit test method.
    */
    class testBackend
    {
    public:
        /*!
         *@brief: test for getSizeMovie method
         */
        void testGetSizeMovies();
        /*!
         *@brief: Testing searching function
         */
        void testSearching();
        /*!
         *@brief: Testing for getFoddSzie method
         */
        void testRecommendation();
    };
}