add_executable(
    test_matrix
    test_matrix.cpp
)

target_link_libraries(
    test_matrix PRIVATE
    nhfmath
    gtest
    gtest_main
)

