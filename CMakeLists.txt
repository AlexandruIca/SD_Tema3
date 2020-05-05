cmake_minimum_required(VERSION 3.10)

project(SD_Tema3 LANGUAGES CXX)

include(cmake/CompilerWarnings.cmake)
include(cmake/StandardProjectSettings.cmake)
include(cmake/Sanitizers.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_14)
enable_sanitizers(project_options)

add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/)
