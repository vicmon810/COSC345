project(MovieFood)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)
# Include directories for mongo-cxx-driver
find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)

#For ultralight
set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            "backend/src/Connection.cpp"
            "backend/include/connection.h")

add_app("${SOURCES}")

# Link libraries
target_link_libraries(MovieFood PRIVATE 
	$<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
	$<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)
