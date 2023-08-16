project(MovieFood)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)
# Include directories for mongo-cxx-driver
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/bsoncxx/v_noabi)
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/mongocxx/v_noabi)

# Link directories for mongo-cxx-driver
link_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/lib)






#For ultralight

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            "backend/src/Connection.cpp"
            "backend/include/connection.h")

add_app("${SOURCES}")



# Link libraries
target_link_libraries(MovieFood PRIVATE bsoncxx mongocxx)
