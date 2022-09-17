# Project #01: Something about C++ Programming

If you are new to C++, the following book will be a good textbook.
- [*C++ Primer (5th Edition)*. Stanley B. Lippman, et al. Addison-Wesley, 2013.](https://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113)

If you already master the syntax of C++ and you write high-quality C++ code, the following books will help you.
- [*Effective C++ (3rd Edition)*. Scott Meyers. Addison-Wesley, 2017](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876)
- [*More effective C++*. Scott Meyers. Addison-Wesley, 2014](https://www.amazon.com/More-Effective-Improve-Programs-Designs/dp/020163371X)
- [*Effective Modern C++*. Scott Meyers. O'Reilly, 2018](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996)


## Designing Vec3d Class


* [vec3d.hpp](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2301/vec3d-class/src/vec3d.hpp)
* [vec3d.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2301/vec3d-class/src/vec3d.cpp)




## Namespace





## Building with CMake

if we want to compile a simple program with a single source file `source.cpp` , we can directly compile it by calling the compiler.

```shell
g++ -o prog source.cpp
```

But when we try to build a large program, things get complicated. 



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




## Benchmark