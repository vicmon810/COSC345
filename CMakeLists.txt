cmake_minimum_required(VERSION 3.12)
project(MovidAndFood)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)

# Add the source file to the project
add_executable(MovieAndFood Connection.cpp)

target_link_libraries(MovieAndFood PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)
target_link_libraries(MovieAndFood PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)
