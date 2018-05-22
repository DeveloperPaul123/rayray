
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(raytracer)

set(project_headers
    include/raytracer/core/nd_base.h
    include/raytracer/core/point.h
    include/raytracer/core/vector.h 
    include/raytracer/core/ray.h)

set(project_sources
    src/ray.cpp)

add_library(${PROJECT_NAME} ${project_headers} ${project_sources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        include
)

if(RAYRAY_BUILD_TESTS)
    set(project_test_name "${PROJECT_NAME}.tests")
    set(project_test_sources 
        tests/unit_tests.cpp)
    add_executable(${project_test_name} ${project_test_sources})
    target_link_libraries(${project_test_name} 
        PUBLIC
            ${PROJECT_NAME}
            GTest::GTest
            GTest::Main
    )
    add_dependencies(${project_test_name} GTest::GTest GTest::Main)
endif(RAYRAY_BUILD_TESTS)
