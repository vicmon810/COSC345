project(MovieFood)
cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 17)
include(cmake/App.cmake)
include(cmake/FindBSONCXX.cmake)
include(cmake/FindMONGOCXX.cmake)
# Find packages using CMake Find Modules
find_package(bsoncxx REQUIRED)
find_package(mongocxx REQUIRED)
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
set_target_properties(MovieFood PROPERTIES AUTOMOC ON)
set_target_properties(MovieFood PROPERTIES AUTOUIC ON)

target_link_libraries(MovieFood PRIVATE 
	$<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
	$<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)
