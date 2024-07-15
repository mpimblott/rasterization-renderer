#pragma once

#include <array>
#include "vector.h"
#include <vector>

struct Geometry {
  std::vector<Vec3> points;
  std::vector<int> faces;
};