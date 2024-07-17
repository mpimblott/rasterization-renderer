#include "geometry.h"

const double pi = std::acos(-1);

Point3h::Point3h()
{
  data[3] = 1;
}

Point3h::Point3h(std::initializer_list<float> v)
{
  assert(v.size() == 3 && "Vector initialiser list has incorrect size.");
  std::copy(v.begin(), v.end(), data.begin());
  data[3] = 1;
}

Point3h::Point3h(Vec<float, 4> &v)
{
  data[0] = v[0];
  data[1] = v[1];
  data[2] = v[2];
  data[3] = 1;
}

float Point3h::norm() const
{
  return sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
}

Point3h Point3h::unit() const
{
  float n = norm();
  return Point3h({data[0] / n, data[1] / n, data[2] / n});
}

Point3h rotateX(Point3h &v, float angle)
{
  Matf4 m = {{1, 0, 0, 0}, {0, static_cast<float>(cos(angle)), static_cast<float>(-1 * sin(angle)), 0}, {0, static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0}, {0, 0, 0, 1}};
  std::cout << m * transpose(v) << std::endl;
  auto k = m * transpose(v);
  std::cout << transpose(m * transpose(v)) << std::endl;
  return e1h;
}