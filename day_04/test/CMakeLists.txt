include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(day04p01_test 
    test_d04p1.c 
    ${PROJECT_SOURCE_DIR}/src/d04p1.c
)
add_executable(day04p02_test 
    test_d04p2.c
    ${PROJECT_SOURCE_DIR}/src/d04p2.c
)


target_link_libraries(day04p01_test vector)
target_link_libraries(day04p02_test vector)

target_include_directories(day04p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/Vector)
target_include_directories(day04p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/Vector)

add_test(
    NAME "day04_test_part1" 
    COMMAND day04p01_test
)

add_test(
    NAME "day04_test_part2" 
    COMMAND day04p02_test
)