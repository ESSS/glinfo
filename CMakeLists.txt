cmake_minimum_required(VERSION 3.5.2)

project(glinfo LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../eden/cmake)
include(Config)

# Dependencies

#add_definitions(-DROCKY_CORE)

add_subdirectory(source/c++/glinfo)

#include(ExportTargets)
#generate_export_targets_file(vbo_benchmark_export)
