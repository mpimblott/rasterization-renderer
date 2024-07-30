#pragma once

#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cassert>
#include <random>

#include "point.h"
#include "geometry.h"

using std::make_unique;
using std::unique_ptr;
using std::make_shared;
using std::shared_ptr;

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
  ColourRGB random_colour();
  size_t find_n_stringstream_chunks(std::stringstream &ss);
  size_t find_n_stringstream_chunks(std::stringstream &ss, char delimiter);
  void parse_face(std::stringstream &ss, unique_ptr<std::vector<Triangle>> &triangles);
  Point3h parse_vertex(std::stringstream &ss);
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
};