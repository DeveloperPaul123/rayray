cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(sandbox)

set(project_sources 
    src/main.cpp)

add_executable(${PROJECT_NAME} ${project_sources})

target_link_libraries(${PROJECT_NAME} PUBLIC raytracer)