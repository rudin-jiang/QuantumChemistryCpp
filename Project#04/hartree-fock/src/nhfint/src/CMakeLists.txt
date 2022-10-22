add_library(
    nhfint
    basisfile.cpp
    tho_basis.cpp
    tho_int.cpp
)

target_include_directories(
    nhfint PUBLIC
    .
)

target_link_libraries(
    nhfint
    nhfstr
    nhfmath
)