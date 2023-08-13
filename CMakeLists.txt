project(MovieFood)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

#For ultralight

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp")

add_app("${SOURCES}")