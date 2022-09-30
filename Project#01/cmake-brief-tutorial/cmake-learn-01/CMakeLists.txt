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
    prog            # program name
    source.cpp      # source file name
)