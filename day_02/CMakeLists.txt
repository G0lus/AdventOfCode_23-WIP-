project(day02 LANGUAGES C)

SET(CMAKE_C_COMPILE_FEATURES OFF)
SET(CMAKE_C_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD 99)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc)

add_executable( day02 
    ${PROJECT_SOURCE_DIR}/src/main.c 
    ${PROJECT_SOURCE_DIR}/src/d02p1.c 
    ${PROJECT_SOURCE_DIR}/src/d02p2.c
)

target_include_directories(day02 PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_link_libraries(day02 vector)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)