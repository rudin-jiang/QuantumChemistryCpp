# Project #01: Something about C++ Programming

This tutorial mainly teaches you how to write your own quantum chemistry programs, and programming skills in C++ should be a prerequisite. Here are some things you should know.

* The fundamentals of C++: variables, expressions, statements, control structures and functions.
* Classes and objects. You'd better understand some object-oriented programming ideas.
* The Standard Template Library (STL). Be able to use vector, set and map at least.

If you are new to C++, you can start by reading the section of [Crawford group's tutorial](https://github.com/CrawfordGroup/ProgrammingProjects#c-programming-tutorial-in-chemistry) that introduces C++. You can go back to some of the material when you need to use some of the features you don't know yet. If you want to master C++ more comprehensively, I recommend you to read *C++ Primer*.[<sup>[1]</sup>](#ref1)




In this project, we will write a class that is often used in quantum chemistry programs.
（to help us review the C++ language. At the same time we will also learn some tools that are often used when writing large programs.）

## Designing Vec3d Class

In quantum chemistry programs, it is often necessary to define a data type to represent a point in three-dimensional space. In C++, we generally define a class to represent a point. 





* [vec3d.hpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/src/vec3d.hpp)
* [vec3d.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/src/vec3d.cpp)


## Namespace

You should have noticed that the above code has something like the following.

```c++
namespace nhfMath {

// something about Vec3d class

}
```

Here we will explain what this code does. Large programs tend to use independently developed libraries. Such libraries also tend to define a large number of global name. When our program uses different libraries, it is almost inevitable that some of these global names will clash. [Namespaces](https://en.cppreference.com/w/cpp/language/namespace) provide a controlled mechanism for preventing name collisions. Names defined in a namespace are not visible in the global namespace. If you want to use a name defined in the namespace, you need to specify the namespace name. For example, if you want to use `Vec3d` defined in namespace `nhfMath`, you should use `nhfMath::Vec3d`.

在使用 namespace 时需要注意的一些地方

* 不要在namespace内部include头文件
* 不要在namespace内部using其他namespace

* 
* 

In this document, the items related to mathematics, molecular integral, and other quantitative calculation will be classified into the namespace `nhfMath`, `nhfInt`, and `nhf` respectively.

## Building with CMake



When we want to develop large programs, we often need to use build tools. There are many build tools, here we use [CMake](https://cmake.org). CMake is a cross-platform build tool.

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)




```shell
cmake -B build 
cmake --build build
```


## Unit Testing

> The content of this paragraph is not necessary. If you find it difficult to learn, you can first briefly skim through it to understand what this paragraph is introducing, and then learn it in the future when you feel it is necessary.

Bugs in the program are inevitable. [Unit Testing](https://en.wikipedia.org/wiki/Unit_testing) is an extremely effective means of troubleshooting bugs. We will add unit tests to our program so that we will have some confidence in the correctness of the program we have written.

[GoogleTest](https://github.com/google/googletest) a mature C++ unit testing framework, and it is our choice. Below we will briefly describe how to use GoogleTest for unit testing.

Create a new folder called `extern` in the root of our project to hold third-party dependencies. Go into the `extern` folder and clone GoogleTest here.

```shell
mkdir extern
cd extern
git clone git@github.com:google/googletest.git --depth=1

# The effect of "--depth=1"
#    clone the latest committed. File size will be small
```

```
vec3d-class
│   CMakeLists.txt
│
└───src
|   |   CMakeLists.txt
│   │   vec3d.hpp
│   │   vec3d.cpp
|   |   main.cpp
│   
└───extern
    │   googletest
```





```c++
// include this header for google test
#include <gtest/gtest.h>
#include "vec3d.hpp"

// absolute error, used to determine whether 
// two floating-point numbers are equal
const double absErr = 1e-12;

TEST(TestVec3d, TestConstructor) {
    // default constructor
    nhfMath::Vec3d v;
    EXPECT_NEAR(v.x, 0.0, absErr);
    EXPECT_NEAR(v.y, 0.0, absErr);
    EXPECT_NEAR(v.z, 0.0, absErr);

    // value constructor
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v(x, y, z);
        EXPECT_NEAR(v.x, x, absErr);
        EXPECT_NEAR(v.y, y, absErr);
        EXPECT_NEAR(v.z, z, absErr);
    }}}
}
```

下面是我实现的测试代码，给大家参考

* [test_vec3d.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/test/test_vec3d.cpp)


## Benchmark

> The content of this paragraph is not necessary. If you find it difficult to learn, you can first briefly skim through it to understand what this paragraph is introducing, and then learn it in the future when you feel it is necessary.


1. 什么是benchmark
2. 为什么要做benchmark
3. 如何做benchmark


Clone [Google Benchmark](https://github.com/google/benchmark) in `extern` directory and 


## Reference

* <a id="ref1"></a> [1] [*C++ Primer (5th Edition)*. Stanley B. Lippman, et al. Addison-Wesley, 2013.](https://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113)