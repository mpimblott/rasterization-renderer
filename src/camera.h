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
  void set_pos(Point3 &pos);
  void set_lookat(Point3 &v);
  Point3 get_pos() const;
  Vec3 get_lookat() const;
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
  size_t pixelWidth;
  size_t pixelHeight;
  std::vector<float> imgBuffer;
  Point3h defaultPos = Point3h(0, 0, 0);
  Point3h &cam_to_screen(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &screen_to_raster(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &compute_pixel_coordinate(const Point3h &src_pt, Point3h &dst_pt) const;
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
