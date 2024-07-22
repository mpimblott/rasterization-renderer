#pragma once

#include <vector>
#include "point.h"

class Mesh
{
public:
  Mesh() = default;
  void set_vertices(std::vector<Point3h> vertices);
  void set_edges(std::vector<size_t> edges);
  const std::vector<Point3h> &get_vertices() const;
  const std::vector<size_t> &get_edges() const;
private:
  std::vector<Point3h> vertices;
  std::vector<size_t> edges;
};