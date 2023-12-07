project(day01 LANGUAGES C)

SET(CMAKE_C_COMPILE_FEATURES OFF)
SET(CMAKE_C_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD 99)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc)

add_executable( day01 
    ${PROJECT_SOURCE_DIR}/src/main.c 
    ${PROJECT_SOURCE_DIR}/src/d01p1.c 
    ${PROJECT_SOURCE_DIR}/src/d01p2.c
)

target_link_libraries(day01 vector)

target_include_directories(day01 PRIVATE ${CMAKE_SOURCE_DIR}/lib/Vector)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)