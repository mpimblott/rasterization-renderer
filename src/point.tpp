#include "point.h"

const double pi = std::acos(-1);

inline Point3::Point3()
{
  data[0] = 0;
  data[1] = 0;
  data[2] = 0;
}

inline Point3::Point3(float x, float y, float z)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

inline float& Point3::x()
{
  return data[0];
}

inline float& Point3::y()
{
  return data[1];
}

inline float& Point3::z()
{
  return data[2];
}

inline Point3 &Point3::operator=(const Point3 &v)
{
  for (size_t i = 0; i < 3; i++)
  {
    data[i] = v[i];
  }
  return *this;
}

inline Point3 &Point3::operator=(const Vec<float, 3> &v)
{
  for (size_t i = 0; i < 3; i++)
  {
    data[i] = v[i];
  }
  return *this;
}

inline Point3h::Point3h()
{
  data[3] = 1;
}

inline Point3h::Point3h(std::initializer_list<float> v)
{
  assert(v.size() == 3 && "Vector initialiser list has incorrect size.");
  std::copy(v.begin(), v.end(), data.begin());
  data[3] = 1;
}

inline Point3h::Point3h(Vec<float, 4> &v)
{
  data[0] = v[0];
  data[1] = v[1];
  data[2] = v[2];
  data[3] = 1;
}

inline Point3h::Point3h(float x, float y, float z)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
  data[3] = 1;
}

inline float& Point3h::x()
{
  return data[0];
}

inline float& Point3h::y()
{
  return data[1];
}

inline float& Point3h::z()
{
  return data[2];
}


inline float Point3h::norm() const
{
  return sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
}

inline Point3h Point3h::unit() const
{
  float n = norm();
  return Point3h({data[0] / n, data[1] / n, data[2] / n});
}

inline Point3h rotateX(Point3h &v, float angle)
{
  Matf4 m = {{1, 0, 0, 0}, {0, static_cast<float>(cos(angle)), static_cast<float>(-1 * sin(angle)), 0}, {0, static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0}, {0, 0, 0, 1}};
  std::cout << m * transpose(v) << std::endl;
  auto k = m * transpose(v);
  std::cout << transpose(m * transpose(v)) << std::endl;
  return e1h;
}

inline Point3h &Point3h::operator=(const Point3h &v)
{
  for (size_t i = 0; i < 3; i++)
  {
    data[i] = v[i];
  }
  return *this;
}