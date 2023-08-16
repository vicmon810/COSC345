project(MovieFood)
cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 17)
include(cmake/App.cmake)
<<<<<<< HEAD

# Find packages for MongoDB
find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/extrnal/cpp-httplib-master)

# For ultralight
set(SOURCES 
    "src/MyApp.h"
    "src/MyApp.cpp"
    "src/main.cpp"
    "src/Connection.cpp"
    "src/connection.h"
    # Remove the line below, as it's not needed
    # "/path/to/httplib/httplib.h"  
)

add_app("${SOURCES}")

# Link libraries
target_link_libraries(MovieFood PRIVATE 
    $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
    $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)
=======

#For ultralight

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp")

add_app("${SOURCES}")
>>>>>>> 585dffee3f6e468af4119b8d58c6beb8f7776e8a
