#include "vec3d.hpp"
#include <iostream>
#include <string>

int main() {
    nhfMath::Vec3d v1(1,2,3);
    nhfMath::Vec3d v2(4,5,6);

    std::cout << (v1 + v2).to_string() << std::endl;

    return 0;
}