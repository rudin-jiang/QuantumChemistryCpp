cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    vec3d-class
    VERSION 1.0
    LANGUAGES C CXX
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
    add_definitions(-DNOMINMAX)
endif()

add_subdirectory(src)


# test and benchmark
add_subdirectory(extern/googletest)
# add_subdirectory(extern/benchmark)
add_subdirectory(test)
