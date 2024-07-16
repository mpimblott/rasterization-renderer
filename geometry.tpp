#include "geometry.h"

Point3H::Point3H()
{
  data[3] = 1;
}

Point3H::Point3H(std::initializer_list<float> v)
{
  assert(v.size() == 3 && "Vector initialzer list has incorrect size.");
  std::copy(v.begin(), v.end(), data.begin());
  data[3] = 1;
}