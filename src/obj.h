#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "geometry.h"
#include "point.h"

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

class MeshLoader {
 public:
  virtual shared_ptr<Mesh> load(const char *file) = 0;
};

class ObjLoader : MeshLoader {
 public:
  ObjLoader();
  shared_ptr<Mesh> load(const char *file);

 private:
  void initRNG();
  size_t coloursRequired = 0;
  bool computeSmoothNormals = true;
  ColourRGB random_colour();
  size_t find_n_stringstream_chunks(std::stringstream &ss);
  size_t find_n_stringstream_chunks(std::stringstream &ss, char delimiter);
  void parse_face(std::stringstream &ss, std::vector<Triangle> &triangles);
  void parse_triangle_face(std::stringstream &ss, std::vector<Triangle> &triangles);
  void parse_polygon_face(std::stringstream &ss, std::vector<Triangle> &triangles, size_t nVertices);
  Point3h parse_vertex(std::stringstream &ss);
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  void compute_smooth_normals(std::vector<Triangle> &triangles, const std::vector<Vertex> &vertices);
};