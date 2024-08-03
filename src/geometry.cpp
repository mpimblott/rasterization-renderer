#include "geometry.h"

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
  os << "[Triangle - verts: ";
  for (size_t i = 0; i < triangle.nVertices; i++) {
    os << triangle.vertexIndices[i] << ", ";
  }
  os << "colours: ";
  for (size_t i = 0; i < triangle.nVertices; i++) {
    os << triangle.vertexColourIndices[i] << ", ";
  }
  os << "]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const MeshBase &mesh) {
  os << "[Mesh - \nverts: \n";
  for (size_t i = 0; i < mesh.data->vertices->size(); i++) {
    os << (*mesh.data->vertices)[i] << ", ";
  }
  // os << "\nvertexColours: \n";
  // for (size_t i = 0; i < mesh.vertexColours->size(); i++) {
  //   os << (*mesh.vertexColours)[i] << ", ";
  // }
  os << "\ntriangles: \n";
  for (size_t i = 0; i < mesh.data->triangles->size(); i++) {
    os << (*mesh.data->triangles)[i] << ", \n";
  }
  os << "]";
  return os;
}

Vec3h Triangle::normal(const std::vector<Point3h> &vertexData) const {
  return cross(vertexData[vertexIndices[0]], vertexData[vertexIndices[1]]).normalise();
}

const size_t Mesh::get_n_faces() const { return data->triangles->size(); }

const std::vector<Point3h> &Mesh::get_vertices() const { return (*data->vertices);}

const Triangle &Mesh::get_triangle(size_t i) const {
  assert(i < (*data->triangles).size() && "Attempt to access mesh triangle out of bounds.");
  return (*data->triangles)[i];
}

const ColourRGB &VertexColourDecorator::get_vertex_colour(size_t i) const {
  assert(i < (*vertexColours).size() && "Attempt to access mesh vertex colour out of bounds.");
  return (*vertexColours)[i];
}

const size_t Mesh::get_n_vertices() const { return (*data->vertices).size(); }

const Point3h &Mesh::get_vertex(size_t i) const {
  assert(i < (*data->vertices).size() && "Attempt to access mesh vertex out of bounds.");
  return (*data->vertices)[i];
}

// void MeshList::add(shared_ptr<Mesh> mesh) { objects.push_back(mesh); }