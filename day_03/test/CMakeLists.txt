include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(day03p01_test 
    test_d03p1.c 
    ${PROJECT_SOURCE_DIR}/src/d03p1.c
)
add_executable(day03p02_test 
    test_d03p2.c
    ${PROJECT_SOURCE_DIR}/src/d03p2.c
)


target_link_libraries(day03p01_test vector)
target_link_libraries(day03p02_test vector)

target_include_directories(day03p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_include_directories(day03p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)

add_test(
    NAME "day03_test_part1" 
    COMMAND day03p01_test
)

add_test(
    NAME "day03_test_part2" 
    COMMAND day03p02_test
)