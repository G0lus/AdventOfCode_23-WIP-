include_directories(../inc)

add_executable(day01p01_test 
    test_d01p1.c 
    ${PROJECT_SOURCE_DIR}/src/d01p1.c
)
add_executable(day01p02_test 
    test_d01p2.c
    ${PROJECT_SOURCE_DIR}/src/d01p2.c
)


target_link_libraries(day01p01_test vector)
target_link_libraries(day01p02_test vector)

target_include_directories(day01p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_include_directories(day01p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)

add_test(
    NAME "day01_test_part1" 
    COMMAND day01p01_test
)

add_test(
    NAME "day01_test_part2" 
    COMMAND day01p02_test
)