# Uncomment section for your respective OS
# For windows
cmake_minimum_required(VERSION 3.12)
project(MovidAndFood)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)

# Add the source file to the project
add_executable(MovieAndFood 
				Connection.cpp
				main.cpp
				)

target_link_libraries(MovieAndFood PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)
target_link_libraries(MovieAndFood PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

# For MAC
#cmake_minimum_required(VERSION 3.12)
#project(MovidAndFood)

#set(CMAKE_CXX_STANDARD 17)

# Find the required Qt components
#find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Include directories for mongo-cxx-driver
#include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/bsoncxx/v_noabi) # Please change this to your own mongo-cxx-driver location
#include_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/include/mongocxx/v_noabi) # Please change this to your own mongo-cxx-driver location

# Link directories for mongo-cxx-driver
#link_directories(/usr/local/Cellar/mongo-cxx-driver/3.8.0/lib) # Please change this to your own mongo-cxx-driver location

# Add the source file to the project
#add_executable(MovidAndFood Connection.cpp main.cpp )

# Link libraries
#target_link_libraries(MovidAndFood PRIVATE Qt5::Widgets Qt5::Core)
#target_link_libraries(MovidAndFood PRIVATE bsoncxx mongocxx)

