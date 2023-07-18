# cmake_minimum_required(VERSION 3.12)
# project(MovidAndFood)

# set(CMAKE_CXX_STANDARD 11)

# # Include directories
# include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/bsoncxx/v_noabi) # Please change this to your own mongo-cxx-driver location
# include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/mongocxx/v_noabi) # Please change this to your own mongo-cxx-driver location

# # Link directories
# link_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/lib) # Please change this to your own mongo-cxx-driver location

# # Find the required Qt components
# find_package(Qt5 REQUIRED COMPONENTS Core)

# # Add the source file to the project
# add_executable(MovidAndFood Connection.cpp)

# # Link libraries
# target_link_libraries(MovidAndFood PRIVATE bsoncxx mongocxx)
# target_link_libraries(MovidAndFood PRIVATE Qt5::Core)

cmake_minimum_required(VERSION 3.12)
project(MovidAndFood)

set(CMAKE_CXX_STANDARD 11)

# Find the required Qt components
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Include directories for mongo-cxx-driver
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/bsoncxx/v_noabi) # Please change this to your own mongo-cxx-driver location
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/mongocxx/v_noabi) # Please change this to your own mongo-cxx-driver location

# Link directories for mongo-cxx-driver
link_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/lib) # Please change this to your own mongo-cxx-driver location

# Add the source file to the project
add_executable(MovidAndFood Connection.cpp main.cpp GUI.cpp)

# Link libraries
target_link_libraries(MovidAndFood PRIVATE Qt5::Widgets Qt5::Core)
target_link_libraries(MovidAndFood PRIVATE bsoncxx mongocxx)

