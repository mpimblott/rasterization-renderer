#pragma once

#include "memory"

#include "vector.h"
#include "point.h"
#include "math.h"
#include "ppm.h"
#include "geometry.h"

using std::shared_ptr;
using std::make_shared;
using colour = float;

class Camera
{
public:
  Camera(float viewportWidth, float viewportHeight, size_t pixelsX, size_t pixelsY);
  Matf4 wld2cam() const;
  Matf4 cam2wld() const;
  void setPos(Point3 &pos);
  void setLookat(Point3 &v);
  Point3 getPos() const;
  Vec3 getLookat() const;
  void build_buffer(Mesh &mesh);
  void render(MeshList& scene);
  const std::vector<float> &get_buffer() const;
  Mesh build_projection(Mesh &mesh);
  bool test_point(float x, float y, Mesh &mesh);

private:
  void init();
  Matf4 camMat;
  float viewportWidth;
  float viewportHeight;
  size_t pixelsX;
  size_t pixelsY;
  std::vector<float> imgBuffer;
  Point3h defaultPos = Point3h(0, 0, 0);
  Point3h &camToScreen(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &screenToRaster(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &computePixelCoordinate(const Point3h &src_pt, Point3h &dst_pt) const;
  bool pineda_edge(float x, float y, Point3h p0, Point3h p1);
};

class Renderer
{
public:
  Renderer() = default;
  ~Renderer() = default;
  virtual void render(size_t width, size_t height, const std::vector<float> &imgBuffer) = 0;
};

class ppmRenderer: public Renderer {
public:
  void render(size_t width, size_t height, const std::vector<float> &imgBuffer) override;
};
