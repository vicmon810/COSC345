find_path(MONGOCXX_INCLUDE_DIR NAMES mongocxx/instance.hpp)
find_library(MONGOCXX_LIB NAMES mongocxx)

if (MONGOCXX_INCLUDE_DIR AND MONGOCXX_LIB)
    set(MONGOCXX_FOUND TRUE)
endif ()

if (MONGOCXX_FOUND)
    set(MONGOCXX_INCLUDE_DIRS ${MONGOCXX_INCLUDE_DIR})
    set(MONGOCXX_LIBRARIES ${MONGOCXX_LIB})
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MONGOCXX DEFAULT_MSG MONGOCXX_LIBRARIES MONGOCXX_INCLUDE_DIRS)
