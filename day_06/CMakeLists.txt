project(day06 LANGUAGES C)

SET(CMAKE_C_COMPILE_FEATURES OFF)
SET(CMAKE_C_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD 99)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc)

add_executable( day06 
    ${PROJECT_SOURCE_DIR}/src/main.c 
    ${PROJECT_SOURCE_DIR}/src/d06p1.c 
    ${PROJECT_SOURCE_DIR}/src/d06p2.c
)
    
target_include_directories(day06 PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_link_libraries(day06 vector)

target_include_directories(day06 PRIVATE ${CMAKE_SOURCE_DIR}/lib/strutils)
target_link_libraries(day06 strutils)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)