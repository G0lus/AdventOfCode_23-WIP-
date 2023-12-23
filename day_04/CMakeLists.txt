project(day04 LANGUAGES C)

SET(CMAKE_C_COMPILE_FEATURES OFF)
SET(CMAKE_C_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD 99)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc)

    
link_libraries(m)
add_executable( day04 
    ${PROJECT_SOURCE_DIR}/src/main.c 
    ${PROJECT_SOURCE_DIR}/src/d04p1.c 
    ${PROJECT_SOURCE_DIR}/src/d04p2.c
)
    
target_include_directories(day04 PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_link_libraries(day04 vector)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)