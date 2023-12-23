include_directories(../inc)

add_executable(day02p01_test 
    test_d02p1.c 
    ${PROJECT_SOURCE_DIR}/src/d02p1.c
)
add_executable(day02p02_test 
    test_d02p2.c
    ${PROJECT_SOURCE_DIR}/src/d02p2.c
)


target_link_libraries(day02p01_test vector)
target_link_libraries(day02p02_test vector)

target_include_directories(day02p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_include_directories(day02p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)

add_test(
    NAME "day02_test_part1" 
    COMMAND day02p01_test
)

add_test(
    NAME "day02_test_part2" 
    COMMAND day02p02_test
)