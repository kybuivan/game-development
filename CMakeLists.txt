cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

project(game-development)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/cmake/external)
include(add_module)
add_subdirectory(core)
add_subdirectory(sdl2)