cmake_minimum_required(VERSION 3.5.2)

project(glinfo LANGUAGES CXX)

if(NOT "$ENV{CONDA_BUILD}" STREQUAL "1")
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../eden/cmake)
    include(Config)
endif()

# Dependencies

add_subdirectory(source/c++/glinfo)
