cmake_minimum_required(VERSION 3.12)
project(MovidAndFood)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/bsoncxx/v_noabi) ##Please chanage this to YOUSELF's mongo-xcc-driver location in YOU OWN machine
include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/mongocxx/v_noabi)##Please chanage this to YOUSELF's mongo-xcc-driver location in YOU OWN machine

# Link directories
link_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/lib)##Please chanage this to YOUSELF's mongo-xcc-driver location in YOU OWN machine

# Add the source file to the project
add_executable(MovidAndFood Connection.cpp)

# Link libraries
target_link_libraries(MovidAndFood bsoncxx mongocxx)
