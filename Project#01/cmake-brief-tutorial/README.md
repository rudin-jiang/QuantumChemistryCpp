# A Brief Tutorial of CMake

## 我们为什么需要CMake



## 第一个CMake工程


```cmake
cmake_minimum_required(VERSION 3.11)

# c++ standard we want to use
set(CMAKE_CXX_STANDARD 11)

# if we don't turn on this, cmake will use old standard
# when the compiler don't support c++ standard we ask
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# turn off compiler extensions
# for producing correct programs 
# when we use different compilers
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    cmake-learn-01      # project name
    VERSION 1.0         # version of our project
    LANGUAGES C CXX     # language we use
)

add_executable(
    prog                # program name
    source.cpp          # source file name
)
```

```shell
# create a new directory named build
# and project will be compiled in it
cmake -B build

# build the project in build directory
cmake --build build

# 
./build/prog
```

## Targets in CMake

[cmake-buildsystem](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)

Each target in CMake corresponds to an executable or library. Executables and libraries are defined using the `add_executable()` and `add_library()` commands. For example,
```cmake
add_library(libraryName sourceFile1.cpp sourceFile2.cpp)
add_executable(programName sourceFile3.cpp sourceFile4.cpp)
```
will compile 


## put code in src directory



## link library


## include directory

