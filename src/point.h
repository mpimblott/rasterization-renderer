#pragma once

#include <cassert>
#include <array>
#include "vector.h"
#include <vector>
#include <cmath>

class Point3 : public Vec<float, 3>
{
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

class Point3h : public Vec<float, 4>
{
public:
  Point3h();
  Point3h(std::initializer_list<float> v);
  Point3h(Vec<float, 4> &v);
  Point3h(float x, float y, float z);
  float &x();
  float &y();
  float &z();
  const float &x() const;
  const float &y() const;
  const float &z() const;
  float norm() const;
  Point3h unit() const;
  Point3h &operator=(const Point3h &v);
};

const Point3h e1h = {1, 0, 0};
const Point3h e2h = {0, 1, 0};
const Point3h e3h = {0, 0, 1};

template <typename T, size_t N>
inline Point3h rotate_x(Vec<float, 3> &v, double angle);

using Vec3h = Point3h;
using Vec3 = Point3;

#include "point.tpp"