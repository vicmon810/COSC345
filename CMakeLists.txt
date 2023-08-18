cmake_minimum_required(VERSION 3.12)
project(MovieAndFood)

set(CMAKE_CXX_STANDARD 17)

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(MovieAndFood 
    src/Connection.cpp
    include/Connection.h
    src/main.cpp
    include/Recommendation.h 
    src/Recommendation.cpp)

set_target_properties(MovieAndFood PROPERTIES AUTOMOC ON)
set_target_properties(MovieAndFood PROPERTIES AUTOUIC ON)

target_link_libraries(MovieAndFood PRIVATE 
    $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
    $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
