cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(rayray)

set(USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
option(RAYRAY_BUILD_TESTS "Turn on to build unit tests." OFF)

if(RAYRAY_BUILD_TESTS)
    include(ExternalGoogleTest)
endif(RAYRAY_BUILD_TESTS)

add_subdirectory(raytracer)
