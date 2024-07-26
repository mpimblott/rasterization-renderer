#pragma once

#include "point.h"
#include <array>
#include <cassert>
#include <memory>
#include <vector>

using std::array;
using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;

class Mesh;

using triangle = std::array<size_t, 3>;

std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

class Mesh {
public:
  Mesh() = default;
  // Mesh(std::vector<Point3h> vertices, std::vector<size_t> indices,
  // std::vector<Point3h> normals);
  Mesh(size_t totalNonUniqueVertices,
       unique_ptr<std::vector<size_t>> vertexOrderingIndices,
       unique_ptr<std::vector<Point3h>> vertices,
       unique_ptr<std::vector<Point3h>> normals,
       unique_ptr<std::vector<Vec<float, 2>>> textureCoordinates,
       unique_ptr<std::vector<Vec<float, 3>>> vertexColours);

  const size_t get_n_faces() const;
  const size_t &get_total_non_unique_vertices() const;
  const std::vector<size_t> &get_vertex_ordering_indices() const;
  const size_t get_n_vertices() const;
  const std::vector<Point3h> &get_vertices() const;
  const std::vector<Point3h> &get_normals() const;
  const std::vector<Vec<float, 2>> &get_texture_coordinates() const;
  const Point3h &get_vertex(size_t i) const;
  const size_t &get_vertex_order_idx(size_t i) const;
  const Vec<float, 3> &get_vertex_colour(size_t i) const;
  // Vec<float, 3> copy_vertex_colour(size_t i) const;
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh);

private:
  size_t totalNonUniqueVertices;
  unique_ptr<std::vector<size_t>>
      vertexOrderingIndices;                 // stores the vertex ordering data
  unique_ptr<std::vector<Point3h>> vertices; // the vertices
  unique_ptr<std::vector<Point3h>> normals;  // the normals to each face
  unique_ptr<std::vector<Vec<float, 2>>> textureCoordinates;
  unique_ptr<std::vector<Vec<float, 3>>> vertexColours;
};

class MeshList {
public:
  MeshList() = default;
  void add(shared_ptr<Mesh> mesh);

private:
  std::vector<shared_ptr<Mesh>> objects;
};