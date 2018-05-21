# This file will download and configure google testing
cmake_minimum_required(VERSION 2.8.8)

include(cmake/Externals.cmake)

find_package(Git REQUIRED)
if(NOT Git_FOUND)
    message(FATAL_ERROR "Git is required!")
endif(NOT Git_FOUND)

# ensure to build shared libs on all platforms
# except for windows. Not really needed for this project.
if(WIN32)
    set(_BUILD_SHARED_LIBS OFF)
else(WIN32)
    set(_BUILD_SHARED_LIBS ON)
endif(WIN32)

list(APPEND GTEST_CMAKE_ARGS 
    "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}"
    "-Dgtest_force_shared_crt=ON"
    "-DBUILD_GTEST=ON"
    "-DBUILD_SHARED_LIBS=${_BUILD_SHARED_LIBS}"
    "-DCMAKE_DEBUG_POSTFIX=${CMAKE_DEBUG_POSTFIX}")

ExternalProject_Add(GoogleTestExternal
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "718fd88d8f145c63b8cc134cf8fed92743cc112f"
    CMAKE_ARGS ${GTEST_CMAKE_ARGS}
    PREFIX "${EXTERNAL_BUILD_DIR}"
	# Disable install step
    INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(GoogleTestExternal source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)

# Specify MainTest's link libraries
ExternalProject_Get_Property(GoogleTestExternal binary_dir)
set(GTEST_LIBS_DIR ${binary_dir}/googlemock/gtest)

# workaround for cmake bug where it complains that interface target
# include non-existant path.
file(MAKE_DIRECTORY ${GTEST_INCLUDE_DIRS})

add_library(GTest::GTest UNKNOWN IMPORTED)
add_library(GTest::Main UNKNOWN IMPORTED)
set(intermediate_path_debug "Debug")
set(intermediate_path_release "Release")

set(gtest_lib_name "gtest")
set(gtest_lib_name_debug "${gtest_lib_name}d")

if(UNIX)
    set(intermediate_path_debug "")
    set(intermediate_path_release "")
    set(gtest_lib_name_debug "${gtest_lib_name}")
endif(UNIX)

set_target_properties(GTest::GTest PROPERTIES
    IMPORTED_LOCATION_DEBUG ${GTEST_LIBS_DIR}/${intermediate_path_debug}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_DEBUG_POSTFIX}${CMAKE_FIND_LIBRARY_SUFFIXES}
    IMPORTED_LOCATION_RELEASE ${GTEST_LIBS_DIR}/${intermediate_path_release}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})

set_target_properties(GTest::Main PROPERTIES
    IMPORTED_LOCATION_DEBUG ${GTEST_LIBS_DIR}/${intermediate_path_debug}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_DEBUG_POSTFIX}${CMAKE_FIND_LIBRARY_SUFFIXES}
    IMPORTED_LOCATION_RELEASE ${GTEST_LIBS_DIR}/${intermediate_path_release}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})

add_dependencies(GTest::GTest GoogleTestExternal)
add_dependencies(GTest::Main GTest::GTest)