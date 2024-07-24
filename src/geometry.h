#pragma once

#include <memory>
#include <vector>
#include "point.h"

using std::shared_ptr;
using std::make_shared;

class Mesh;

std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

class Mesh
{
public:
  Mesh() = default;
  Mesh(std::vector<Point3h> vertices, std::vector<size_t> indices);
  void set_vertices(std::vector<Point3h> vertices);
  void set_indices(std::vector<size_t> edges);
  const std::vector<Point3h> &get_vertices() const;
  const std::vector<size_t> &get_indices() const;
  void add_vertex(Point3h p);

  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh);
private:
  std::vector<Point3h> vertices;
  std::vector<size_t> indices;
};

class MeshList
{
public:
  MeshList() = default;
  void add(shared_ptr<Mesh> mesh);
private:
  std::vector<shared_ptr<Mesh>> objects;
};