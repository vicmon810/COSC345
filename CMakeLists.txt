cmake_minimum_required(VERSION 3.12)
project(MovieAndFood)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "--coverage")


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Test REQUIRED)

file(COPY ${CMAKE_SOURCE_DIR}/data/Movies.csv DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/data/Food.csv DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/data/curated2.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/searchIcon.png DESTINATION ${CMAKE_BINARY_DIR})
add_executable(MovieAndFood 
    src/connection.h
    src/Connection.cpp
    src/Recommendation.h 
    src/Recommendation.cpp
    src/imageDownload.h
    src/imageDownload.cpp
    src/clickImage.h
    src/clickImage.cpp
    src/clickHandler.h
    src/clickHandler.cpp
    src/main.cpp 
    )

    
    
    
# Add the QSS file to your project
file(COPY ${CMAKE_SOURCE_DIR}/src/myStyles.qss DESTINATION ${CMAKE_BINARY_DIR})

# Add the QSS file to your executable's sources
target_sources(MovieAndFood PRIVATE ${CMAKE_BINARY_DIR}/myStyles.qss)


set_target_properties(MovieAndFood PROPERTIES AUTOMOC ON)
set_target_properties(MovieAndFood PROPERTIES AUTOUIC ON)

target_link_libraries(MovieAndFood PRIVATE 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::Test
    )



add_executable(UnitTest
   test/TestMain.cpp
    test/testBackend.h
    test/testBackend.cpp
    test/testFrontend.h
    test/testFrontend.cpp
    src/connection.h
    src/Connection.cpp
    src/Recommendation.h
    src/Recommendation.cpp
    src/clickHandler.h
    src/clickHandler.cpp
)

target_link_libraries(UnitTest PRIVATE 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::Test
)


set_target_properties(UnitTest PROPERTIES AUTOMOC ON)
set_source_files_properties(test/TestFrontend.cpp PROPERTIES SKIP_AUTOMOC ON)


target_link_libraries(UnitTest PRIVATE  Qt5::Test)


# Include Catch2 test discovery
include(CTest)