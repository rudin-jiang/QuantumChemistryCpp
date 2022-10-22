add_subdirectory(nhfstr)
add_subdirectory(nhfmath)
add_subdirectory(nhfint)

add_library(
    nhf
    atomlist.cpp
)

target_include_directories(
    nhf PUBLIC
    .
)