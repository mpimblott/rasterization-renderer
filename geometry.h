#pragma once

#include <cassert>
#include <array>
#include "vector.h"
#include <vector>

class Point3 : public Vec<float, 3>
{
  using Vec::Vec;

public:
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
  Property<float> z = this->data[2];
};

class Point3H : public Vec<float, 4>
{
public:
  Point3H();
  Point3H(std::initializer_list<float> v);
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
  Property<float> z = this->data[2];
};

#include "geometry.tpp"