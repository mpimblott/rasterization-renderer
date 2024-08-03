#include "geometry.h"

std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
  os << "[Triangle - verts: ";
  for (size_t i = 0; i < triangle.nVertices; i++) {
    os << triangle.vertexIndices[i] << ", ";
  }
  // os << "texCoords: ";
  // for (size_t i = 0; i < triangle.nVertices; i++) {
  //   os << triangle.textureCoordIndices[i] << ", ";
  // }
  // os << "normals: ";
  // for (size_t i = 0; i < triangle.nVertices; i++) {
  //   os << triangle.normalIndices[i] << ", ";
  // }
  os << "colours: ";
  for (size_t i = 0; i < triangle.nVertices; i++) {
    os << triangle.vertexColourIndices[i] << ", ";
  }
  os << "]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
  os << "[Mesh - \nverts: \n";
  for (size_t i = 0; i < mesh.vertices->size(); i++) {
    os << (*mesh.vertices)[i] << ", ";
  }
  // os << "\nnormals: \n";
  // for (size_t i = 0; i < mesh.normals->size(); i++) {
  //   os << (*mesh.normals)[i] << ", ";
  // }
  os << "\ntexCoords: \n";
  for (size_t i = 0; i < mesh.textureCoordinates->size(); i++) {
    os << (*mesh.textureCoordinates)[i].u << ", " << (*mesh.textureCoordinates)[i].v << ", ";
  }
  os << "\nvertexColours: \n";
  for (size_t i = 0; i < mesh.vertexColours->size(); i++) {
    os << (*mesh.vertexColours)[i] << ", ";
  }
  os << "\ntriangles: \n";
  for (size_t i = 0; i < mesh.triangles->size(); i++) {
    os << (*mesh.triangles)[i] << ", \n";
  }
  os << "]";
  return os;
}

Vec3h Triangle::normal(const std::vector<Point3h> &vertexData) const {
  return cross(vertexData[vertexIndices[0]], vertexData[vertexIndices[1]]).normalise();
}

const size_t Mesh::get_n_faces() const { return triangles->size(); }

const Triangle &Mesh::get_triangle(size_t i) const {
  assert(i < (*triangles).size() && "Attempt to access mesh triangle out of bounds.");
  return (*triangles)[i];
}

const ColourRGB &Mesh::get_vertex_colour(size_t i) const {
  assert(i < (*vertexColours).size() && "Attempt to access mesh vertex colour out of bounds.");
  return (*vertexColours)[i];
}

const size_t Mesh::get_n_vertices() const { return (*vertices).size(); }

const Point3h &Mesh::get_vertex(size_t i) const {
  assert(i < (*vertices).size() && "Attempt to access mesh vertex out of bounds.");
  return (*vertices)[i];
}

Mesh::Mesh(unique_ptr<std::vector<Triangle>> triangles, unique_ptr<std::vector<Point3h>> vertices,
           unique_ptr<std::vector<TextureCoord>> textureCoordinates, unique_ptr<std::vector<ColourRGB>> vertexColours)
    : triangles(std::move(triangles)),
      vertices(std::move(vertices)),
      textureCoordinates(std::move(textureCoordinates)),
      vertexColours(std::move(vertexColours)) {}

void MeshList::add(shared_ptr<Mesh> mesh) { objects.push_back(mesh); }