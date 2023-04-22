cmake_minimum_required(VERSION 3.24)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(procedural-terrain-with-opengl)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/vendors/cpp-logger/Includes)
add_subdirectory(vendors/cpp-logger)

add_subdirectory(Renderer)
add_subdirectory(ProceduralGeneration)
add_subdirectory(Game)
