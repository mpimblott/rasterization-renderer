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
  Camera(size_t width, size_t height, float fov, float nearClipping, float farClipping);
  const Matf4 &world_to_cam_mat() const;
  const Matf4 cam_to_world_mat() const;
  const Matf4 &projection_mat() const;
  void set_near_clipping_distance(float distance);
  void set_far_clipping_distance(float distance);
  void set_fov(float angle);
  void set_pos(Point3 &pos);
  Point3 get_pos() const;
  void build_buffer(Mesh &mesh);
  const std::vector<float> &get_buffer() const;
  void vertex_shader(const Point3h &vertex, const Matf4 &projectionMatrix, const Matf4 &worldToCameraMatrix, Point3h &out);

private:
  void init();
  Matf4 camMat;
  Matf4 projectionMat;
  void recompute_projection_mat();
  float viewportWidth;
  float viewportHeight;
  size_t pixelWidth;
  size_t pixelHeight;
  float nearClippingDistance = 1;
  float farClippingDistance = 6;
  float fov = 90;
  std::vector<float> imgBuffer;
  Point3h defaultPos = Point3h(0, 0, 0);
  Point3h &cam_to_screen(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &screen_to_raster(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &compute_pixel_coordinate(const Point3h &src_pt, Point3h &dst_pt) const;
  Mesh build_projection(Mesh &mesh);
  bool test_point(float x, float y, Mesh &mesh);
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
