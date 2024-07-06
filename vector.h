#pragma once

#include <cstdlib>
#include <iostream>
#include "util.h"

template <size_t SIZE>
class Vec
{
public:
  Vec();
  size_t len();
  float &operator[](size_t i);
  const float &operator[](size_t i) const;
  Vec<SIZE> operator+(Vec<SIZE> &v) const;
  Vec<SIZE> operator-(Vec<SIZE> &v) const;
  Vec<SIZE> operator*(float s) const;
  Vec<SIZE> operator/(float s) const;
  float dot(Vec<SIZE> &v);
  Vec<SIZE> cross(Vec<SIZE> &v);
  Vec<SIZE> normalize();
  friend std::ostream &operator<<(std::ostream &os, const Vec<SIZE> &v)
  {
    os << "(";
    for (size_t i = 0; i < SIZE; i++)
    {
      os << v[i];
      if (i < SIZE - 1)
        os << ", ";
    }
    os << ")";
    return os;
  }

protected:
  float data[SIZE];
};

class Vec2: public Vec<2>
{
public:
  Vec2();
  Vec2(float x, float y);
  Property x;
  Property y;
};

class Vec3: public Vec<3>
{
public:
  Vec3();
  Vec3(float x, float y, float z);
  Property x;
  Property y;
  Property z;
};



