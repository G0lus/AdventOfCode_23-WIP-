include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(day06p01_test 
    test_d06p1.c 
    ${PROJECT_SOURCE_DIR}/src/d06p1.c
)
add_executable(day06p02_test 
    test_d06p2.c
    ${PROJECT_SOURCE_DIR}/src/d06p2.c
)

target_link_libraries(day06p01_test vector)
target_link_libraries(day06p02_test vector)
target_link_libraries(day06p01_test strutils)
target_link_libraries(day06p02_test strutils)

target_include_directories(day06p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_include_directories(day06p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/vector)
target_include_directories(day06p01_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/strutils)
target_include_directories(day06p02_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/strutils)


add_test(
    NAME "day06_test_part1" 
    COMMAND day06p01_test
)

add_test(
    NAME "day06_test_part2" 
    COMMAND day06p02_test
)