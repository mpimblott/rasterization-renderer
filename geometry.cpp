#include "geometry.h"

void Mesh::set_edges(std::vector<size_t> edges)
{
  this->edges = edges;
}

void Mesh::set_vertices(std::vector<Point3h> vertices)
{
  this->vertices = vertices;
}

const std::vector<Point3h> &Mesh::get_vertices() const
{
  return vertices;
}

const std::vector<size_t> &Mesh::get_edges() const
{
  return edges;
}