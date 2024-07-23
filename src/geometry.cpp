#include "geometry.h"

std::ostream &operator<<(std::ostream &os, const Mesh &mesh)
{
    os << "[Mesh - verts: ";
  const std::vector<Point3h> &verts = mesh.get_vertices();
  const std::vector<size_t> &indcs = mesh.get_indices();
  for (size_t i = 0; i < verts.size(); i++)
  {
    os << verts[i] << ", ";
  }
  os << "indcs: ";
    for (size_t i = 0; i < indcs.size(); i++)
  {
    os << indcs[i] << ", ";
  }
  os << "]";
  return os;
}

Mesh::Mesh(std::vector<Point3h> vertices, std::vector<size_t> indices)
{
  this->vertices = vertices;
  this->indices = indices;
}

void Mesh::set_indices(std::vector<size_t> indices)
{
  this->indices = indices;
}

void Mesh::set_vertices(std::vector<Point3h> vertices)
{
  this->vertices = vertices;
}

const std::vector<Point3h> &Mesh::get_vertices() const
{
  return vertices;
}

const std::vector<size_t> &Mesh::get_indices() const
{
  return indices;
}

bool Mesh::pineda_edge(Point3h pTest, Point3h p0, Point3h p1)
{
  return (((pTest.x() - p0.x()) * (p1.y() - p0.y()) - (pTest.y() - p0.y()) * (p1.x() - p0.x())) >= 0);
}

bool Mesh::test_point(Point3h &p)
{
  bool t = true;
  for (size_t i = 0; i < indices.size() - 1; i++)
  {
    std::cout << indices[i] << " -> " << indices[i + 1] << ": " << pineda_edge(p, vertices[indices[i]], vertices[indices[i + 1]]) << std::endl;
    t = t && pineda_edge(p, vertices[indices[i]], vertices[indices[i + 1]]);
  }
  return t;
}