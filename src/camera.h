#pragma once

#include <memory>
#include <limits>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <tuple>

#include "vector.h"
#include "point.h"
#include "math.h"
#include "ppm.h"
#include "geometry.h"

using std::make_shared;
using std::shared_ptr;
using colour = float;
using ColourRGBA = Vec<float, 4>;

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
  std::vector<float> build_img_buffer(const Mesh &mesh);
  void vertex_shader(const Point3h &vertex,
                     const Matf4 &projectionMatrix,
                     const Matf4 &worldToCameraMatrix, Point3h &out);
  void texture_shader(const Mesh &mesh,
                      ColourRGBA &out,
                      const float &w0,
                      const float &w1,
                      const float &w2,
                      const Vec<float, 3> &c0,
                      const Vec<float, 3> &c1,
                      const Vec<float, 3> &c2,
                      const float &z);

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
  Point3h defaultPos = Point3h(0, 0, 0);
  Point3h &cam_to_screen(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &screen_to_raster(const Point3h &src_pt, Point3h &dst_pt) const;
  Point3h &compute_pixel_coordinate(const Point3h &src_pt, Point3h &dst_pt) const;
  std::vector<Point3h> project_vertices(const Mesh &meshPtr);
  float pineda_edge(const Point3h &p, const Point3h &p0, const Point3h &p1);
  // returns [xmax, xmin, ymax, ymin] defining bbox in raster space
  std::tuple<size_t, size_t, size_t, size_t> triangle_raster_bbox(
      const Point3h &a,
      const Point3h &b,
      const Point3h &c,
      size_t xMaximumLimit,
      size_t yMaximumLimit);
};

class Renderer
{
public:
  Renderer() = default;
  ~Renderer() = default;
  virtual void render(size_t width, size_t height, const std::vector<float> &imgBuffer) = 0;
};

class ppmRenderer : public Renderer
{
public:
  void render(size_t width, size_t height, const std::vector<float> &imgBuffer) override;
};
