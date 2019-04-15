cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(rayray)

set(USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
option(RAYRAY_BUILD_TESTS "Turn on to build unit tests." OFF)

if(RAYRAY_BUILD_TESTS)
    find_package(GTest)
    if(NOT GTest_FOUND)
        message(STATUS "Could not find GTest including external project.")
        include(ExternalGoogleTest)
    endif(NOT GTest_FOUND)
endif(RAYRAY_BUILD_TESTS)

add_subdirectory(raytracer)
add_subdirectory(sandbox)