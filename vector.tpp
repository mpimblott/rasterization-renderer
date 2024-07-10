#include "vector.h"

template <typename T, size_t SIZE>
Vec<T, SIZE>::Vec(T (&v)[SIZE])
{ // brackets to pass ref to array, rather than array of references
  data = v;
}

template <typename T, size_t SIZE>
Vec<T, SIZE>::Vec(std::initializer_list<T> v)
{
  assert(v.size() == SIZE && "Vector initialzer list has incorrect size.");
  std::copy(v.begin(), v.end(), data.begin());
}

template <typename T, size_t SIZE>
size_t Vec<T, SIZE>::len()
{
  return SIZE;
}

template <typename T, size_t SIZE>
T &Vec<T, SIZE>::operator[](size_t i)
{
  return data[i];
}

template <typename T, size_t SIZE>
const T &Vec<T, SIZE>::operator[](size_t i) const
{
  return data[i];
}

template <typename T, size_t SIZE>
Vec<T, SIZE> Vec<T, SIZE>::operator+(Vec<T, SIZE> &v) const
{
  Vec<T, SIZE> out;
  for (size_t i = 0; i < SIZE; i++)
    out[i] = data[i] + v[i];
  return out;
}

template <typename T, size_t SIZE>
Vec<T, SIZE> Vec<T, SIZE>::operator-(Vec<T, SIZE> &v) const
{
  Vec<T, SIZE> out;
  for (size_t i = 0; i < SIZE; i++)
    out[i] = data[i] - v[i];
  return out;
}

template <typename T, size_t SIZE>
Vec<T, SIZE> Vec<T, SIZE>::operator*(T s) const
{
  Vec<T, SIZE> out;
  for (size_t i = 0; i < SIZE; i++)
    out[i] = data[i] * s;
  return out;
}

template <typename T, size_t SIZE>
Vec<T, SIZE> Vec<T, SIZE>::operator/(T s) const
{
  Vec<T, SIZE> out;
  for (size_t i = 0; i < SIZE; i++)
  {
    out[i] = data[i] / s;
  }
  return out;
}

template <typename T, size_t SIZE>
T Vec<T, SIZE>::dot(Vec<T, SIZE> &v)
{
  T out;
  for (size_t i = 0; i < SIZE; i++)
  {
    out += data[i] * v[i];
  }
  return out;
}

template <size_t SIZE>
VecF<SIZE>::VecF()
{
  for (size_t i = 0; i < SIZE; i++)
    this->data[i] = 0.0f;
}

Vec2::Vec2(float x, float y) : x(data[0]), y(data[1]) {}

// Vec3::Vec3() : x(data[0]), y(data[1]), z(data[2]){};

Vec3::Vec3(float x, float y, float z) : x(data[0]), y(data[1]), z(data[2]) {}
