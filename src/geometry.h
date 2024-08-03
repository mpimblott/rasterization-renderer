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

class MeshBase;
struct Triangle;
using Vertex = Point3h;

std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
std::ostream &operator<<(std::ostream &os, const MeshBase &mesh);

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
  Vec3h normal(const std::vector<Point3h> &vertexData) const;
};

struct MeshData {
  MeshData(unique_ptr<std::vector<Triangle>> triangles, unique_ptr<std::vector<Point3h>> vertices)
      : vertices(std::move(vertices)), triangles(std::move(triangles)){};
  const unique_ptr<const std::vector<Point3h>> vertices;
  const unique_ptr<const std::vector<Triangle>> triangles;
};

class MeshBase {
 public:
  MeshBase(shared_ptr<MeshData> data) : data(data){};

  virtual const size_t get_n_faces() const = 0;
  virtual const size_t get_n_vertices() const = 0;
  virtual const std::vector<Point3h> &get_vertices() const = 0;
  virtual const Vertex &get_vertex(size_t i) const = 0;
  virtual const Triangle &get_triangle(size_t i) const = 0;
  friend std::ostream &operator<<(std::ostream &os, const MeshBase &mesh);

 protected:
  shared_ptr<MeshData> data;
};

class Mesh : public MeshBase {
 public:
  Mesh(shared_ptr<MeshData> data) : MeshBase(data){};
  const size_t get_n_faces() const override;
  const size_t get_n_vertices() const override;
  const std::vector<Point3h> &get_vertices() const override;
  const Vertex &get_vertex(size_t i) const override;
  const Triangle &get_triangle(size_t i) const override;
};

class MeshDecoratorBase : public MeshBase {
 public:
  MeshDecoratorBase(shared_ptr<MeshData> data, unique_ptr<MeshBase> mesh) : MeshBase(data), mesh_(std::move(mesh)){};

  const size_t get_n_faces() const override { return mesh_->get_n_faces(); };
  const size_t get_n_vertices() const override { return mesh_->get_n_vertices(); };
  const std::vector<Point3h> &get_vertices() const { return mesh_->get_vertices(); };
  const Vertex &get_vertex(size_t i) const { return mesh_->get_vertex(i); };
  const Triangle &get_triangle(size_t i) const { return mesh_->get_triangle(i); };

 protected:
  unique_ptr<MeshBase> mesh_;
};

class VertexColourDecorator : public MeshDecoratorBase {
 public:
  VertexColourDecorator(shared_ptr<MeshData> data, unique_ptr<MeshBase> mesh,
                        unique_ptr<std::vector<Vec<float, 3>>> vertexColours)
      : MeshDecoratorBase(data, std::move(mesh)), vertexColours(std::move(vertexColours)){};
  const ColourRGB &get_vertex_colour(size_t i) const;

  const size_t get_n_faces() const override { return mesh_->get_n_faces(); };
  const size_t get_n_vertices() const override { return mesh_->get_n_vertices(); };
  const std::vector<Point3h> &get_vertices() const { return mesh_->get_vertices(); };
  const Vertex &get_vertex(size_t i) const { return mesh_->get_vertex(i); };
  const Triangle &get_triangle(size_t i) const { return mesh_->get_triangle(i); };

 protected:
  unique_ptr<std::vector<ColourRGB>> vertexColours;
};

/*
 * Normals that are per-face for flat shading
 */
// class FaceNormalDecorator : public MeshDecoratorBase {
//  public:
//   FaceNormalDecorator(shared_ptr<MeshData> data, unique_ptr<MeshBase> mesh, unique_ptr<std::vector<Point3h>> normals)
//       : MeshDecoratorBase(data, std::move(mesh)), normals(std::move(normals)){};

//  protected:
//   unique_ptr<std::vector<Point3h>> normals;
// };

/*
 * Normals that are per-vertex for phong shading
 */
// class VertexNormalDecorator : public MeshDecoratorBase {
//  public:
//   VertexNormalDecorator(shared_ptr<MeshData> data, unique_ptr<MeshBase> mesh, unique_ptr<std::vector<Point3h>>
//   normals)
//       : MeshDecoratorBase(data, std::move(mesh)), normals(std::move(normals)){};

//  protected:
//   unique_ptr<std::vector<Point3h>> normals;
// };

// class MeshList {
//  public:
//   MeshList() = default;
//   void add(shared_ptr<Mesh> mesh);

//  private:
//   std::vector<shared_ptr<Mesh>> objects;
// };