cmake_minimum_required(VERSION 3.12)
project(MovieAndFood)
# Add local project module path so CMake includes custom CMake modules.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}cmake/Modules")
include_directories("${CMAKE_SOURCE_DIR}/test")  # Assuming catch.hpp is in the test directory

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Add the source files to the project
add_executable(MovieAndFood 
				src/Connection.cpp
				src/main.cpp
				src/GUI.cpp
				test/main.cpp
				test/test_conn.cpp
				)
				
# Set AUTOMOC and AUTOUIC to automatically handle Qt's moc and uic
set_target_properties(MovieAndFood PROPERTIES AUTOMOC ON)
set_target_properties(MovieAndFood PROPERTIES AUTOUIC ON)

target_link_libraries(MovieAndFood PRIVATE 
	$<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
	$<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

# Create a library target for the Catch header-only test framework.
add_library(Catch INTERFACE)
target_include_directories(Catch
    INTERFACE
            test/
)

# Create a target for executing the Catch unit tests
add_executable(unit_tests
    test/main.cpp
    test/test_conn.cpp
)
target_include_directories(unit_tests
    PUBLIC 
            test/
)
target_link_libraries(
    unit_tests
    PRIVATE
    Catch
)

target_compile_options(unit_tests
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)



install(
	TARGETS unit_tests
	RUNTIME DESTINATION bin
)

# This must always be last!
include(CPack)
