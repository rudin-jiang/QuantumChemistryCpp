#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cmath>
#include "vec3d.hpp"

const double absErr = 1e-12;
const double eps    = 1e-14;

TEST(TestVec3d, TestConstructor) {
    // default constructor
    nhfMath::Vec3d v;
    EXPECT_NEAR(v.x, 0, absErr);
    EXPECT_NEAR(v.y, 0, absErr);
    EXPECT_NEAR(v.z, 0, absErr);

    // value constructor
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v(x, y, z);
        EXPECT_NEAR(v.x, x, absErr);
        EXPECT_NEAR(v.y, y, absErr);
        EXPECT_NEAR(v.z, z, absErr);
    }}}

    // std::string input
    for (double x = -10.0; x <= 10.0; x += 2.5){
    for (double y = -10.0; y <= 10.0; y += 2.5){
    for (double z = -10.0; z <= 10.0; z += 2.5){
        std::string input = 
            std::to_string(x) + " " +
            std::to_string(y) + " " +
            std::to_string(z);
        nhfMath::Vec3d v(input);
        EXPECT_NEAR(v.x, x, absErr);
        EXPECT_NEAR(v.y, y, absErr);
        EXPECT_NEAR(v.z, z, absErr);
    }}}
}

TEST(TestVec3d, TestLen) {
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v(x, y, z);
        double len = std::sqrt(x*x + y*y + z*z);
        EXPECT_NEAR(v.len(), len, absErr);
    }}}
}

TEST(TestVec3d, TestLen2) {
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v(x, y, z);
        double len2 = x*x + y*y + z*z;
        EXPECT_NEAR(v.len2(), len2, absErr);
    }}}
}

TEST(TestVec3d, TestToString) {
    for (double x = -10.0; x <= 10.0; x += 2.5){
    for (double y = -10.0; y <= 10.0; y += 2.5){
    for (double z = -10.0; z <= 10.0; z += 2.5){
        nhfMath::Vec3d v1(x, y, z);
        nhfMath::Vec3d v2(v1.to_string());
        EXPECT_NEAR(v2.x, x, absErr);
        EXPECT_NEAR(v2.y, y, absErr);
        EXPECT_NEAR(v2.z, z, absErr);
    }}}
}

TEST(TestVec3d, TestCompoundOperator) {
    // Vec3d and Vec3d
    for (double x1 = -10.0; x1 <= 10.0; x1 += 2.5){
    for (double y1 = -10.0; y1 <= 10.0; y1 += 2.5){
    for (double z1 = -10.0; z1 <= 10.0; z1 += 2.5){
        nhfMath::Vec3d v(x1, y1, z1);

        for (double x2 = -10.0; x2 <= 10.0; x2 += 2.5){
        for (double y2 = -10.0; y2 <= 10.0; y2 += 2.5){
        for (double z2 = -10.0; z2 <= 10.0; z2 += 2.5){
            nhfMath::Vec3d v1(x2, y2, z2);
            nhfMath::Vec3d v2(x2, y2, z2);
            nhfMath::Vec3d v3(x2, y2, z2);
            nhfMath::Vec3d v4(x2, y2, z2);
            
            v1 += v;
            EXPECT_NEAR(v1.x, x2 + x1, absErr);
            EXPECT_NEAR(v1.y, y2 + y1, absErr);
            EXPECT_NEAR(v1.z, z2 + z1, absErr);

            v2 -= v;
            EXPECT_NEAR(v2.x, x2 - x1, absErr);
            EXPECT_NEAR(v2.y, y2 - y1, absErr);
            EXPECT_NEAR(v2.z, z2 - z1, absErr);

            v3 *= v;
            EXPECT_NEAR(v3.x, x2 * x1, absErr);
            EXPECT_NEAR(v3.y, y2 * y1, absErr);
            EXPECT_NEAR(v3.z, z2 * z1, absErr);

            if (std::abs(x1) > eps && std::abs(y1) > eps 
                                   && std::abs(z1) > eps) {
                v4 /= v;
                EXPECT_NEAR(v4.x, x2 / x1, absErr);
                EXPECT_NEAR(v4.y, y2 / y1, absErr);
                EXPECT_NEAR(v4.z, z2 / z1, absErr);
            }
        }}}
    }}}

    // Vec3d and val
    for (double val = -10.0; val <= 10.0; val += 0.5) {
        for (double x = -10.0; x <= 10.0; x += 2.5){
        for (double y = -10.0; y <= 10.0; y += 2.5){
        for (double z = -10.0; z <= 10.0; z += 2.5){
            nhfMath::Vec3d v1(x, y, z);
            nhfMath::Vec3d v2(x, y, z);
            nhfMath::Vec3d v3(x, y, z);
            nhfMath::Vec3d v4(x, y, z);
            
            v1 += val;
            EXPECT_NEAR(v1.x, x + val, absErr);
            EXPECT_NEAR(v1.y, y + val, absErr);
            EXPECT_NEAR(v1.z, z + val, absErr);

            v2 -= val;
            EXPECT_NEAR(v2.x, x - val, absErr);
            EXPECT_NEAR(v2.y, y - val, absErr);
            EXPECT_NEAR(v2.z, z - val, absErr);

            v3 *= val;
            EXPECT_NEAR(v3.x, x * val, absErr);
            EXPECT_NEAR(v3.y, y * val, absErr);
            EXPECT_NEAR(v3.z, z * val, absErr);

            if (std::abs(val) > eps) {
                v4 /= val;
                EXPECT_NEAR(v4.x, x / val, absErr);
                EXPECT_NEAR(v4.y, y / val, absErr);
                EXPECT_NEAR(v4.z, z / val, absErr);
            }
        }}}
    }
}


TEST(TestVec3d, TestNormOperator) {

    // positive and negative
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v(x, y, z);
        nhfMath::Vec3d pv = +v;
        nhfMath::Vec3d nv = -v;
        
        EXPECT_NEAR(pv.x, x, absErr);
        EXPECT_NEAR(pv.y, y, absErr);
        EXPECT_NEAR(pv.z, z, absErr);

        EXPECT_NEAR(nv.x, -x, absErr);
        EXPECT_NEAR(nv.y, -y, absErr);
        EXPECT_NEAR(nv.z, -z, absErr);
    }}}

    // Vec3d and Vec3d
    for (double x1 = -10.0; x1 <= 10.0; x1 += 2.5) {
    for (double y1 = -10.0; y1 <= 10.0; y1 += 2.5) {
    for (double z1 = -10.0; z1 <= 10.0; z1 += 2.5) {
        nhfMath::Vec3d v1(x1, y1, z1);
        for (double x2 = -10.0; x2 <= 10.0; x2 += 2.5) {
        for (double y2 = -10.0; y2 <= 10.0; y2 += 2.5) {
        for (double z2 = -10.0; z2 <= 10.0; z2 += 2.5) {
            nhfMath::Vec3d v2(x2, y2, z2);

            nhfMath::Vec3d addv = v1 + v2;
            EXPECT_NEAR(addv.x, x1 + x2, absErr);
            EXPECT_NEAR(addv.y, y1 + y2, absErr);
            EXPECT_NEAR(addv.z, z1 + z2, absErr);

            nhfMath::Vec3d misv = v1 - v2;
            EXPECT_NEAR(misv.x, x1 - x2, absErr);
            EXPECT_NEAR(misv.y, y1 - y2, absErr);
            EXPECT_NEAR(misv.z, z1 - z2, absErr);

            nhfMath::Vec3d multv = v1 * v2;
            EXPECT_NEAR(multv.x, x1 * x2, absErr);
            EXPECT_NEAR(multv.y, y1 * y2, absErr);
            EXPECT_NEAR(multv.z, z1 * z2, absErr);

            if (std::abs(x2) > eps && std::abs(y2) > eps 
                                   && std::abs(z2) > eps) {
                nhfMath::Vec3d divv = v1 / v2;
                EXPECT_NEAR(divv.x, x1 / x2, absErr);
                EXPECT_NEAR(divv.y, y1 / y2, absErr);
                EXPECT_NEAR(divv.z, z1 / z2, absErr);
            }
        }}}
    }}}

    // Vec3d and value
    for (double val = -10.0; val <= 10.0; val += 0.5) {
        for (double x = -10.0; x <= 10.0; x += 2.5){
        for (double y = -10.0; y <= 10.0; y += 2.5){
        for (double z = -10.0; z <= 10.0; z += 2.5){
            nhfMath::Vec3d v(x, y, z);
            
            nhfMath::Vec3d v1 = v + val;
            EXPECT_NEAR(v1.x, x + val, absErr);
            EXPECT_NEAR(v1.y, y + val, absErr);
            EXPECT_NEAR(v1.z, z + val, absErr);

            nhfMath::Vec3d v2 = v - val;
            EXPECT_NEAR(v2.x, x - val, absErr);
            EXPECT_NEAR(v2.y, y - val, absErr);
            EXPECT_NEAR(v2.z, z - val, absErr);

            nhfMath::Vec3d v3 = v * val;
            EXPECT_NEAR(v3.x, x * val, absErr);
            EXPECT_NEAR(v3.y, y * val, absErr);
            EXPECT_NEAR(v3.z, z * val, absErr);

            if (std::abs(val) > eps) {
                nhfMath::Vec3d v4 = v / val;
                EXPECT_NEAR(v4.x, x / val, absErr);
                EXPECT_NEAR(v4.y, y / val, absErr);
                EXPECT_NEAR(v4.z, z / val, absErr);
            }
        }}}
    }

    // value and Vec3d
    for (double val = -10.0; val <= 10.0; val += 0.5) {
        for (double x = -10.0; x <= 10.0; x += 2.5){
        for (double y = -10.0; y <= 10.0; y += 2.5){
        for (double z = -10.0; z <= 10.0; z += 2.5){
            nhfMath::Vec3d v(x, y, z);
            
            nhfMath::Vec3d v1 = val + v;
            EXPECT_NEAR(v1.x, val + x, absErr);
            EXPECT_NEAR(v1.y, val + y, absErr);
            EXPECT_NEAR(v1.z, val + z, absErr);

            nhfMath::Vec3d v2 = val - v;
            EXPECT_NEAR(v2.x, val - x, absErr);
            EXPECT_NEAR(v2.y, val - y, absErr);
            EXPECT_NEAR(v2.z, val - z, absErr);

            nhfMath::Vec3d v3 = val * v;
            EXPECT_NEAR(v3.x, val * x, absErr);
            EXPECT_NEAR(v3.y, val * y, absErr);
            EXPECT_NEAR(v3.z, val * z, absErr);

            if (std::abs(x) > eps && std::abs(y) > eps 
                                  && std::abs(z) > eps) {
                nhfMath::Vec3d v4 = val / v;
                EXPECT_NEAR(v4.x, val / x, absErr);
                EXPECT_NEAR(v4.y, val / y, absErr);
                EXPECT_NEAR(v4.z, val / z, absErr);
            }
        }}}
    }
}

TEST(TestVec3d, TestDotProduct) {
    for (double x1 = -10.0; x1 <= 10.0; x1 += 2.5){
    for (double y1 = -10.0; y1 <= 10.0; y1 += 2.5){
    for (double z1 = -10.0; z1 <= 10.0; z1 += 2.5){
        nhfMath::Vec3d v1(x1, y1, z1);

        for (double x2 = -10.0; x2 <= 10.0; x2 += 2.5){
        for (double y2 = -10.0; y2 <= 10.0; y2 += 2.5){
        for (double z2 = -10.0; z2 <= 10.0; z2 += 2.5){
            nhfMath::Vec3d v2(x2, y2, z2);

            EXPECT_NEAR(v1 % v2, x1*x2 + y1*y2 + z1*z2, absErr);
        }}}
    }}}
}

