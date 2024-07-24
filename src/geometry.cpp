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

void Mesh::add_vertex(Point3h p)
{
  vertices.push_back(p);
}

void MeshList::add(shared_ptr<Mesh> mesh)
{
  objects.push_back(mesh);
}