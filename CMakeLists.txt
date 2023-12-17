cmake_minimum_required(VERSION 3.23)
project(AdventOfCode LANGUAGES C)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(lib)

add_compile_options(-Wall -Werror)

add_subdirectory(day_01)
add_subdirectory(day_02)
add_subdirectory(day_03)
add_subdirectory(day_04)