#pragma once

#include <array>
#include <cassert>
#include <memory>
#include <vector>

#include "point.h"

using std::array;
using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;

class Mesh;
struct Triangle;
using Vertex = Point3h;

std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

struct TextureCoord {
  TextureCoord(float u, float v) : u(u), v(v){};
  float u, v;
};

struct Triangle {
  Triangle(const std::array<size_t, 3> &vertexIndices, const std::array<size_t, 3> &textureCoordIndices,
           const std::array<size_t, 3> &normalIndices, const std::array<size_t, 3> &vertexColourIndices)
      : vertexIndices(vertexIndices),
        textureCoordIndices(textureCoordIndices),
        normalIndices(normalIndices),
        vertexColourIndices(vertexColourIndices){};
  const std::array<size_t, 3> vertexIndices;
  const std::array<size_t, 3> textureCoordIndices;
  const std::array<size_t, 3> normalIndices;
  const std::array<size_t, 3> vertexColourIndices;
  const size_t nVertices = 3;
  friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
};

class Mesh {
 public:
  Mesh() = default;
  Mesh(size_t nFaces, unique_ptr<std::vector<Triangle>> triangles, unique_ptr<std::vector<Point3h>> vertices,
       unique_ptr<std::vector<Point3h>> normals, unique_ptr<std::vector<TextureCoord>> textureCoordinates,
       unique_ptr<std::vector<Vec<float, 3>>> vertexColours);

  const size_t get_n_faces() const;
  const size_t get_n_vertices() const;
  const std::vector<Point3h> &get_vertices() const { return *vertices; }
  const Vertex &get_vertex(size_t i) const;
  const Triangle &get_triangle(size_t i) const;
  const ColourRGB &get_vertex_colour(size_t i) const;
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

 private:
  // core mesh data ----------
  unique_ptr<std::vector<Point3h>> vertices;  // the vertices
  unique_ptr<std::vector<TextureCoord>> textureCoordinates;
  unique_ptr<std::vector<Point3h>> normals;               // the normals to each face
  unique_ptr<std::vector<ColourRGB>> vertexColours;
  // mesh organisation data --
  size_t nFaces;
  unique_ptr<std::vector<Triangle>> triangles;
};

class MeshList {
 public:
  MeshList() = default;
  void add(shared_ptr<Mesh> mesh);

 private:
  std::vector<shared_ptr<Mesh>> objects;
};