#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <vector>

#include "vector.h"

using ColourRGBA = Vec<float, 4>;
using ColourRGB = Vec<float, 3>;

class Point3;
class Point3h;

Point3h operator*(float lhs, const Point3h &rhs);

Point3h operator*(const Point3h &lhs, float rhs);

Point3h operator*(const Point3h &lhs, const Matf4 &rhs);

Point3h cross(const Point3h &lhs, const Point3h &rhs);

class Point3 : public Vec<float, 3> {
   public:
    // using Vec::Vec;
    Point3();
    Point3(float x, float y, float z);
    float &x();
    float &y();
    float &z();
    const float &x() const;
    const float &y() const;
    const float &z() const;
    Point3 &operator=(const Point3 &v);
    Point3 &operator=(const Vec<float, 3> &v);
};

class Point3h : public Vec<float, 4> {
   public:
    Point3h();
    Point3h(std::initializer_list<float> v);
    Point3h(Vec<float, 4> &v);
    Point3h(float x, float y, float z);
    Point3h(float x, float y, float z, float w);
    float &x();
    float &y();
    float &z();
    const float &x() const;
    const float &y() const;
    const float &z() const;
    float norm() const;
    Point3h &normalise();
    Point3h normalise() const;
    Point3h &operator=(const Point3h &v);
    Point3h operator+(const Point3h &v) const;
    Point3h operator-(const Point3h &v) const;
    friend Point3h operator*(float lhs, const Point3h &rhs);
    friend Point3h operator*(const Point3h &lhs, float rhs);
    friend Point3h operator*(const Point3h &lhs, const Matf4 &rhs);
};

const Point3h e1h = {1, 0, 0};
const Point3h e2h = {0, 1, 0};
const Point3h e3h = {0, 0, 1};

template <typename T, size_t N>
inline Point3h rotate_x(Vec<float, 3> &v, double angle);

using Vec3h = Point3h;
using Vec3 = Point3;

#include "point.tpp"