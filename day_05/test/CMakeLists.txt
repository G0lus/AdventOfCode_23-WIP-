include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(day05p01_test 
    test_d05p1.c 
    ${PROJECT_SOURCE_DIR}/src/d05p1.c
)
add_executable(day05p02_test 
    test_d05p2.c
    ${PROJECT_SOURCE_DIR}/src/d05p2.c
)

target_link_libraries(day05p01_test vector)
# target_link_libraries(day05p02_test vector)

target_include_directories(day05p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
# target_include_directories(day05p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)


add_test(
    NAME "day05_test_part1" 
    COMMAND day05p01_test
)

add_test(
    NAME "day05_test_part2" 
    COMMAND day05p02_test
)