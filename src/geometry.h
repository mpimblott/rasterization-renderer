#pragma once

#include <vector>
#include "point.h"

class Mesh;

std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

class Mesh
{
public:
  Mesh() = default;
  Mesh(std::vector<Point3h> vertices, std::vector<size_t> edges);
  void set_vertices(std::vector<Point3h> vertices);
  void set_indices(std::vector<size_t> edges);
  const std::vector<Point3h> &get_vertices() const;
  const std::vector<size_t> &get_indices() const;
  bool test_point(Point3h &p);
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh);
private:
  std::vector<Point3h> vertices;
  std::vector<size_t> indices;
  bool pineda_edge(Point3h pTest, Point3h p0, Point3h p1);
};