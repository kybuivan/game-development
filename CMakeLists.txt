cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

project(myProj)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/cmake/external)
include(add_module)
add_subdirectory(core)
add_subdirectory(editor)

add_subdirectory(app)