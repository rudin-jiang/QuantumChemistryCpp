#pragma once

namespace nhfInt {
namespace tho {

double gauss_int_overlap(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2);

double gauss_int_kinetic(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2);

double gauss_int_nuclear(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2,
                         double Zx, double Zy, double Zz);

double gauss_int_repulsion(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                           double alpha2, int l2, int m2, int n2, double x2, double y2, double z2,
                           double alpha3, int l3, int m3, int n3, double x3, double y3, double z3,
                           double alpha4, int l4, int m4, int n4, double x4, double y4, double z4);

}  // namespace (tho)
}  // namespace (nhfInt)