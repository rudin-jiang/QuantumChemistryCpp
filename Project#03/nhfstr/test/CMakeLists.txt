add_executable(
    test_nhfstr
    test_nhfstr.cpp
)

target_link_libraries(
    test_nhfstr PRIVATE
    nhfstr
    gtest
    gtest_main
)