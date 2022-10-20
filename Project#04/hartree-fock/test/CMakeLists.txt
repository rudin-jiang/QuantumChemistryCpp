add_executable(
    test_atomlist
    test_atomlist.cpp
)

target_link_libraries(
    test_atomlist PRIVATE
    nhf
    gtest
    gtest_main
)