#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cmath>
#include "vec3d.hpp"

const double absErr = 1e-12;

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
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
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
    for (double x = -10.0; x <= 10.0; x += 0.1){
    for (double y = -10.0; y <= 10.0; y += 0.1){
    for (double z = -10.0; z <= 10.0; z += 0.1){
        nhfMath::Vec3d v1(x, y, z);
        nhfMath::Vec3d v2(v1.to_string());
        EXPECT_NEAR(v2.x, x, absErr);
        EXPECT_NEAR(v2.y, y, absErr);
        EXPECT_NEAR(v2.z, z, absErr);
    }}}
}

TEST(TestVec3d, TestCompoundOperator) {
    
}








