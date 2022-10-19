# Vec3d
add_executable(
    test_vec3d
    test_vec3d.cpp
)

target_link_libraries(
    test_vec3d PRIVATE
    nhfmath
    gtest
    gtest_main
)


# Matrix
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


# mathfun
add_executable(
    test_mathfun
    test_mathfun.cpp
)

target_link_libraries(
    test_mathfun PRIVATE
    nhfmath
    gtest
    gtest_main
)
