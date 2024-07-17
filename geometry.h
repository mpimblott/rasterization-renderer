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
};

const Point3h e1h = {1, 0, 0};
const Point3h e2h = {0, 1, 0};
const Point3h e3h = {0, 0, 1};

template <typename T, size_t N>
Point3h rotateX(Point3h &v, double angle);

#include "geometry.tpp"