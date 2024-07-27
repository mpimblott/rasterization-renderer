#include "geometry.h"

std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
  os << "[Mesh - verts: ";
  const std::vector<Point3h> &verts = mesh.get_vertices();
  const std::vector<size_t> &indcs = mesh.get_vertex_ordering_indices();
  for (size_t i = 0; i < verts.size(); i++) {
    os << verts[i] << ", ";
  }
  os << "indcs: ";
  for (size_t i = 0; i < indcs.size(); i++) {
    os << indcs[i] << ", ";
  }
  os << "]";
  return os;
}

const size_t Mesh::get_n_faces() const { return nFaces; }

const size_t Mesh::get_total_non_unique_vertices() const { return (*vertexOrderingIndices).size(); }

const std::vector<size_t> &Mesh::get_vertex_ordering_indices() const { return *vertexOrderingIndices; }

const size_t &Mesh::get_vertex_order_idx(size_t i) const {
  assert(i < (*vertexOrderingIndices).size() && "Attempt to access mesh ordering index out of bounds.");
  return (*vertexOrderingIndices)[i];
}

const size_t Mesh::get_n_vertices() const { return (*vertices).size(); }

const std::vector<Point3h> &Mesh::get_vertices() const { return *vertices.get(); }

const Point3h &Mesh::get_vertex(size_t i) const {
  assert(i < (*vertices).size() && "Attempt to access mesh vertex out of bounds.");
  return (*vertices)[i];
}

const std::vector<Point3h> &Mesh::get_normals() const { return *normals.get(); }

const std::vector<Vec<float, 2>> &Mesh::get_texture_coordinates() const { return *textureCoordinates; }

const Vec<float, 3> &Mesh::get_vertex_colour(size_t i) const { return (*vertexColours)[i]; }

const size_t &Mesh::get_vertices_in_face(size_t i) const
{
  return (*verticesPerFace)[i];
}

Mesh::Mesh(size_t nFaces, unique_ptr<std::vector<size_t>> vertexOrderingIndices,
           unique_ptr<std::vector<size_t>> verticesPerFace, unique_ptr<std::vector<Point3h>> vertices,
           unique_ptr<std::vector<Point3h>> normals, unique_ptr<std::vector<Vec<float, 2>>> textureCoordinates,
           unique_ptr<std::vector<Vec<float, 3>>> vertexColours)
    : nFaces(nFaces),
      vertexOrderingIndices(std::move(vertexOrderingIndices)),
      verticesPerFace(std::move(verticesPerFace)),
      vertices(std::move(vertices)),
      normals(std::move(normals)),
      textureCoordinates(std::move(textureCoordinates)),
      vertexColours(std::move(vertexColours)) {}

void MeshList::add(shared_ptr<Mesh> mesh) { objects.push_back(mesh); }