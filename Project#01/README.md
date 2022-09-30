# Project #01: Something about C++ Programming




If you are new to C++, the following book will be a good textbook.
- [*C++ Primer (5th Edition)*. Stanley B. Lippman, et al. Addison-Wesley, 2013.](https://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113)

If you already master the syntax of C++ and you write high-quality C++ code, the following books will help you.
- [*Effective C++ (3rd Edition)*. Scott Meyers. Addison-Wesley, 2017](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876)
- [*More effective C++*. Scott Meyers. Addison-Wesley, 2014](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X)
- [*Effective Modern C++*. Scott Meyers. O'Reilly, 2018](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996)


## Designing Vec3d Class

In quantum chemistry programs, it is often necessary to define a data type to represent a point in three-dimensional space. In C++ programs, we generally define a class to represent a point.


* [vec3d.hpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/src/vec3d.hpp)
* [vec3d.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/src/vec3d.cpp)


## Namespace

> Large programs tend to use independently developed libraries. Such libraries also tend to define a large number of global names, such as classes, functions, and templates. When an application uses libraries from many different vendors, it is almost inevitable that some of these names will clash. [Namespaces](https://en.cppreference.com/w/cpp/language/namespace) provide a controlled mechanism for preventing name collisions. Namespaces partition the global namespace. A namespace is a scope. By defining a library’s names inside a namespace, library authors (and users) can avoid the limitations inherent in global names.




在使用 namespace 时需要注意的一些地方

* 不要在namespace内部include头文件
* 不要在namespace内部using其他namespace
* 




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
