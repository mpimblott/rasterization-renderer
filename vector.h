#pragma once

#include <cstdlib>
#include <iostream>

//https://stackoverflow.com/q/44037870
class Property
{
private:
  float& t;
public:
    inline Property(float& a): t(a) {}

    inline void Set(const float &a) { t = a; }
    inline float& Get() { return t; }

    operator float&() { return t; }
    float &operator=(const float &a) { return t = a; }
};

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



