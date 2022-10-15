add_executable(
    test_basisfile
    test_basisfile.cpp
)

target_link_libraries(
    test_basisfile PRIVATE
    nhfint
    gtest
    gtest_main
)