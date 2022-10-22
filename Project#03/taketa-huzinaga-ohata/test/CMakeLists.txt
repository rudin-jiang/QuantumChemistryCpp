add_executable(
    test_tho_basis
    test_tho_basis.cpp
)

target_link_libraries(
    test_tho_basis PRIVATE
    nhfint
    gtest
    gtest_main
)

