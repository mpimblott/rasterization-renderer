#pragma once

#include <cstdlib>
#include <iostream>

template <size_t SIZE>
class Vec
{
public:
  Vec();
  size_t len();
  float &operator[](size_t i);
  const float &operator[](size_t i) const;
  Vec<SIZE> operator+(Vec<SIZE> &v);
  Vec<SIZE> operator-(Vec<SIZE> &v);
  Vec<SIZE> operator*(float s);
  Vec<SIZE> operator/(float s);
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

private:
  float data[SIZE];
};

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;
