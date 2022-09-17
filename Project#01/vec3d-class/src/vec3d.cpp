#include "vec3d.hpp"
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cassert>


namespace nhfMath {


/* constructors */
Vec3d::Vec3d() : x(0), y(0), z(0) {}

Vec3d::Vec3d(double x, double y, double z)
: x(x), y(y), z(z) {}

Vec3d::Vec3d(const std::string &input) {
    std::istringstream iss(input);
    iss >> x >> y >> z;
}

/* member functions */
double Vec3d::len() const { 
    return std::sqrt(x*x + y*y + z*z);
}

double Vec3d::len2() const {
    return x*x + y*y + z*z;
}

std::string Vec3d::to_string() const {
    char buff[1024];
    std::sprintf(buff, " %16.8lf %16.8lf %16.8lf", x, y, z);
    return std::string(buff);
}

/* member operators */
Vec3d&  Vec3d::operator+=(const Vec3d &vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
Vec3d&  Vec3d::operator-=(const Vec3d &vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
Vec3d&  Vec3d::operator*=(const Vec3d &vec) { x *= vec.x; y *= vec.y; z *= vec.z; return *this; }
Vec3d&  Vec3d::operator/=(const Vec3d &vec) { x /= vec.x; y /= vec.y; z /= vec.z; return *this; }
Vec3d&  Vec3d::operator+=(double val) { x += val; y += val; z += val; return *this; }
Vec3d&  Vec3d::operator-=(double val) { x -= val; y -= val; z -= val; return *this; }
Vec3d&  Vec3d::operator*=(double val) { x *= val; y *= val; z *= val; return *this; }
Vec3d&  Vec3d::operator/=(double val) { x /= val; y /= val; z /= val; return *this; }

/*  operators */
Vec3d  operator+(const Vec3d &vec) { return Vec3d(+vec.x, +vec.y, +vec.z); }
Vec3d  operator-(const Vec3d &vec) { return Vec3d(-vec.x, -vec.y, -vec.z); }

Vec3d  operator+(const Vec3d &vec1, const Vec3d &vec2)
{ return Vec3d(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z); }

Vec3d  operator-(const Vec3d &vec1, const Vec3d &vec2)
{ return Vec3d(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z); }

Vec3d  operator*(const Vec3d &vec1, const Vec3d &vec2)
{ return Vec3d(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z); }

Vec3d  operator/(const Vec3d &vec1, const Vec3d &vec2)
{ return Vec3d(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z); }

Vec3d  operator+(const Vec3d &vec, double val)
{ return Vec3d(vec.x + val, vec.y + val, vec.z + val); }

Vec3d  operator-(const Vec3d &vec, double val)
{ return Vec3d(vec.x - val, vec.y - val, vec.z - val); }

Vec3d  operator*(const Vec3d &vec, double val)
{ return Vec3d(vec.x * val, vec.y * val, vec.z * val); }

Vec3d  operator/(const Vec3d &vec, double val)
{ return Vec3d(vec.x / val, vec.y / val, vec.z / val); }

Vec3d  operator+(double val, const Vec3d &vec)
{ return Vec3d(val + vec.x, val + vec.y, val + vec.z); }

Vec3d  operator-(double val, const Vec3d &vec)
{ return Vec3d(val - vec.x, val - vec.y, val - vec.z); }

Vec3d  operator*(double val, const Vec3d &vec)
{ return Vec3d(val * vec.x, val * vec.y, val * vec.z); }

Vec3d  operator/(double val, const Vec3d &vec)
{ return Vec3d(val / vec.x, val / vec.y, val / vec.z); }

/* dot product */
double operator%(const Vec3d &vec1, const Vec3d &vec2)
{ return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z; }

}