find_package(Eigen3 REQUIRED)

add_library(
    nhfmath
    vec3d.cpp
    matrix.cpp
    mathfun.cpp
    constant.cpp
)


target_include_directories(
    nhfmath PUBLIC
    ${EIGEN3_INCLUDE_DIR}
    .
)
