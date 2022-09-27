find_package(Eigen3 REQUIRED)

add_library(
    nhfmath
    matrix.cpp
)


target_include_directories(
    nhfmath PUBLIC
    ${EIGEN3_INCLUDE_DIR}
    .
)
