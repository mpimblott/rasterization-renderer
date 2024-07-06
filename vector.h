#pragma once

#include <cstdlib>
#include <iostream>
#include "util.h"

template <typename T, size_t SIZE>
class Vec
{
public:
  Vec() = default;
  size_t len();
  T &operator[](size_t i);
  const T &operator[](size_t i) const;
  Vec<T, SIZE> operator+(Vec<T, SIZE> &v) const;
  Vec<T, SIZE> operator-(Vec<T, SIZE> &v) const;
  Vec<T, SIZE> operator*(T a) const;
  Vec<T, SIZE> operator/(T a) const;
  T dot(Vec<T, SIZE> &v);
  Vec<T, SIZE> cross(Vec<T, SIZE> &v);
  friend std::ostream &operator<<(std::ostream &os, const Vec<T, SIZE> &v)
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
  T data[SIZE];
};

template <size_t SIZE>
class VecF: public Vec<float, SIZE>
{
public:
  VecF();
};

class Vec2: public VecF<2>
{
public:
  Vec2();
  Vec2(float x, float y);
  Property<float> x;
  Property<float> y;
};

class Vec3: public VecF<3>
{
public:
  Vec3();
  Vec3(float x, float y, float z);
  Property<float> x;
  Property<float> y;
  Property<float> z;
};

#include "vector.tpp"