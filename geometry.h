#pragma once

#include <vector>
#include "point.h"

class Mesh
{
public:
  Mesh() = default;
  void set_vertices();
  void set_edges();
  std::vector<Point3h> get_vertices();
  std::vector<Point3h> get_edges();
private:
  std::vector<Point3h> vertices;
  std::vector<size_t> edges;
};