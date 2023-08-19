cmake_minimum_required(VERSION 3.12)
project(MovieAndFood)

set(CMAKE_CXX_STANDARD 17)


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(COPY ${CMAKE_SOURCE_DIR}/data/Movies.csv DESTINATION ${CMAKE_BINARY_DIR})

add_executable(MovieAndFood 
    src/connection.h
    src/Connection.cpp
    src/main.cpp
    src/Recommendation.h 
    src/Recommendation.cpp)

    # Use the nlohmann_json_INCLUDE_DIRS provided by find_package

set_target_properties(MovieAndFood PROPERTIES AUTOMOC ON)
set_target_properties(MovieAndFood PROPERTIES AUTOUIC ON)

target_link_libraries(MovieAndFood PRIVATE 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
