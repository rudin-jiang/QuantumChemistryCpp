#pragma once

#include <string>

namespace nhfMath {


// Vec3d is a class for representing
// a vector or a point in 3D space.
class Vec3d {
public:
    double x, y, z;

    /* constructors */
    explicit Vec3d();
    explicit Vec3d(double x, double y, double z);
    explicit Vec3d(const std::string &input);

    /* member functions */
    double  len() const;
    double  len2() const;
    std::string to_string() const;

    /* access operator */
    double  operator[](std::size_t i) const;
    double& operator[](std::size_t i);

    /* compound operators */
    Vec3d&  operator+=(const Vec3d &vec);
    Vec3d&  operator-=(const Vec3d &vec);
    Vec3d&  operator*=(const Vec3d &vec);
    Vec3d&  operator/=(const Vec3d &vec);
    Vec3d&  operator+=(double val);
    Vec3d&  operator-=(double val);
    Vec3d&  operator*=(double val);
    Vec3d&  operator/=(double val);
};

Vec3d  operator+(const Vec3d &vec); // positive
Vec3d  operator-(const Vec3d &vec); // negative
Vec3d  operator+(const Vec3d &vec1, const Vec3d &vec2);
Vec3d  operator-(const Vec3d &vec1, const Vec3d &vec2);
Vec3d  operator*(const Vec3d &vec1, const Vec3d &vec2);
Vec3d  operator/(const Vec3d &vec1, const Vec3d &vec2);
Vec3d  operator+(const Vec3d &vec, double val);
Vec3d  operator-(const Vec3d &vec, double val);
Vec3d  operator*(const Vec3d &vec, double val);
Vec3d  operator/(const Vec3d &vec, double val);
Vec3d  operator+(double val, const Vec3d &vec);
Vec3d  operator-(double val, const Vec3d &vec);
Vec3d  operator*(double val, const Vec3d &vec);
Vec3d  operator/(double val, const Vec3d &vec);

/* dot product */
double operator%(const Vec3d &vec1, const Vec3d &vec2);


}   // namespace (nhfMath)