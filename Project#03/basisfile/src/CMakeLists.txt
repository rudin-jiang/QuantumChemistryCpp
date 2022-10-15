add_library(
    nhfint
    basisfile.cpp
)

target_include_directories(
    nhfint PUBLIC
    .
)

target_link_libraries(
    nhfint
    nhfstr
)