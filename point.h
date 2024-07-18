#pragma once

#include <cassert>
#include <array>
#include "vector.h"
#include <vector>
#include <cmath>

class Point3 : public Vec<float, 3>
{
  using Vec::Vec;

public:
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
  Property<float> z = this->data[2];
  Point3 &operator=(const Point3 &v);
};

class Point3h : public Vec<float, 4>
{
public:
  Point3h();
  Point3h(std::initializer_list<float> v);
  Point3h(Vec<float, 4> &v);
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
  Property<float> z = this->data[2];
  float norm() const;
  Point3h unit() const;
  Point3h &operator=(const Point3h &v);
};

const Point3h e1h = {1, 0, 0};
const Point3h e2h = {0, 1, 0};
const Point3h e3h = {0, 0, 1};

template <typename T, size_t N>
Point3h rotateX(Vec<float, 3> &v, double angle);

typedef Point3h Vec3h;
typedef Point3 Vec3;

#include "point.tpp"