add_executable(
    test_vec3d
    test_vec3d.cpp
)

target_link_libraries(
    test_vec3d PRIVATE
    nhfMath
    gtest
    gtest_main
)