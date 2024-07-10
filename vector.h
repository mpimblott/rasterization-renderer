#pragma once

#include <array>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "util.h"

template <typename T, size_t SIZE>
class Vec
{
public:
  Vec() = default;
  Vec(T (&v)[SIZE]);
  Vec(std::initializer_list<T> v);
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
  std::array<T, SIZE> data;
};

template <size_t SIZE>
class VecF : public Vec<float, SIZE>
{
public:
  VecF();
  using Vec<float, SIZE>::Vec;
};

class Vec2 : public VecF<2>
{
public:
  using VecF<2>::VecF;
  Vec2(float x, float y);
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
};

class Vec3 : public VecF<3>
{
public:
using VecF<3>::VecF;
  Vec3(float x, float y, float z);
  Property<float> x = this->data[0];
  Property<float> y = this->data[1];
  Property<float> z = this->data[2];
};

#include "vector.tpp"