#include "camera.h"

Camera::Camera(size_t width, size_t height, float fov, float nearClipping, float farClipping)
{
  pixelWidth = width;
  pixelHeight = height;
  this->fov = fov;
  nearClippingDistance = nearClipping;
  farClippingDistance = farClipping;
  init();
}

void Camera::init()
{
  Id(camMat);
  recompute_projection_mat();
  std::vector<float> tmp(pixelWidth * pixelHeight * 3);
  imgBuffer = tmp;
}

const Matf4 &Camera::world_to_cam_mat() const
{
  return camMat;
}

const Matf4 Camera::cam_to_world_mat() const
{
  return inv(camMat);
}

const Matf4 &Camera::projection_mat() const
{
  return projectionMat;
}

void Camera::set_near_clipping_distance(float distance)
{
  nearClippingDistance = distance;
  recompute_projection_mat();
}

void Camera::set_far_clipping_distance(float distance)
{
  farClippingDistance = distance;
  recompute_projection_mat();
}

void Camera::set_fov(float angle)
{
  fov = angle;
  recompute_projection_mat();
}

void Camera::recompute_projection_mat()
{
  // this matrix maps from screen space to NDC space ([-1,1]) accounting for clipping and fov
  // should be pre-multiplication by worldToCam and after should be normalised to [0, 1] for raster space
  float s = (static_cast<float>(1/tan((fov/2)*(pi/180))));
  projectionMat = {{s, 0, 0, 0},
                   {0, s, 0, 0},
                   {0, 0, (-1 * farClippingDistance) / (farClippingDistance - nearClippingDistance), -1},
                   {0, 0, (-1 * farClippingDistance * nearClippingDistance) / (farClippingDistance - nearClippingDistance), 0}};
}

void Camera::set_pos(Point3 &p)
{
  // build the translation matrix from the default position to the desired point
  camMat[3][0] = p[0] - defaultPos[0];
  camMat[3][1] = p[1] - defaultPos[1];
  camMat[3][2] = p[2] - defaultPos[2];
}

Point3 Camera::get_pos() const
{
  return Point3(camMat[3][0], camMat[3][1], camMat[3][2]);
}

Point3h &Camera::cam_to_screen(const Point3h &src_pt, Point3h &dst_pt) const
{
  dst_pt.x() = src_pt.x() / (-1 * src_pt.z());
  dst_pt.y() = src_pt.y() / (-1 * src_pt.z());
  dst_pt.z() = -1 * src_pt.z();
  return dst_pt;
}

/*
  normalise the x and y coordinates in screen space to raster space
  (width and height limited by fov and rounded)
*/
Point3h &Camera::screen_to_raster(const Point3h &src_pt, Point3h &dst_pt) const
{
  float normalised_x = (src_pt.x() + (viewportWidth / 2)) / viewportWidth;
  float normalised_y = (src_pt.y() + (viewportHeight / 2)) / viewportHeight;
  dst_pt.x() = std::floor(normalised_x * pixelWidth);
  dst_pt.y() = std::floor((1 - normalised_y) * pixelHeight);
  return dst_pt;
}

/*
 * compute the raster coordinate of a world coordinate
 */
Point3h &Camera::compute_pixel_coordinate(const Point3h &src_pt, Point3h &dst_pt) const
{
  cam_to_screen(src_pt, dst_pt);
  screen_to_raster(dst_pt, dst_pt);
  return dst_pt;
}


Mesh Camera::build_projection(Mesh &mesh)
{
  Mesh projection;
  projection.set_indices(mesh.get_indices());
  for (const auto &vertex : mesh.get_vertices())
  {
    // create a new mesh with the projections of the points
    Point3h p;
    vertex_shader(vertex, projection_mat(), world_to_cam_mat(), p);
    projection.add_vertex(p);
  }
  return projection;
}

void Camera::build_buffer(Mesh &mesh)
{
  Mesh projection = build_projection(mesh);
  // std::cout << projection << std::endl;
  for (size_t y = 0; y < pixelHeight; y++)
  {
    for (size_t x = 0; x < pixelWidth; x++)
    {
      size_t idx = y * pixelHeight * 3 + 3 * x;
      if (test_point(x, y, projection))
      {
        imgBuffer[idx] = 1.0;
        // std::cout << "true" << std::endl;
      }
      else
      {
        imgBuffer[idx + 1] = 0.1;
      }
    }
  }
}

const std::vector<float> &Camera::get_buffer() const
{
  return imgBuffer;
}

bool Camera::pineda_edge(float x, float y, Point3h p0, Point3h p1)
{
  return (((x - p0.x()) * (p1.y() - p0.y()) - (y - p0.y()) * (p1.x() - p0.x())) >= 0);
}

bool Camera::test_point(float x, float y, Mesh &mesh)
{
  bool t = true;
  for (size_t i = 0; i < mesh.get_indices().size() - 1; i++)
  {
    t = t && pineda_edge(x, y, mesh.get_vertices()[mesh.get_indices()[i]], mesh.get_vertices()[mesh.get_indices()[i + 1]]);
  }
  return t;
}

void ppmRenderer::render(size_t width, size_t height, const std::vector<float> &imgBuffer)
{
  // first line of the image file
  std::cout << "P3\n"
            << width << ' ' << height << "\n255\n";
  for (int j = 0; j < height; j++)
  {
    std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
    for (int i = 0; i < width; i++)
    {
      size_t idx = j * width * 3 + 3 * i;
      std::cout << static_cast<int>(255 * imgBuffer[idx]) << ' '
                << static_cast<int>(255 * imgBuffer[idx + 1]) << ' '
                << static_cast<int>(255 * imgBuffer[idx + 2]) << '\n';
    }
  }
  std::clog << "\rDone.                       \n";
}

void Camera::vertex_shader(const Point3h& vertex, const Matf4 &projectionMatrix, const Matf4 &worldToCameraMatrix, Point3h &out)
{
  out = vertex * worldToCameraMatrix;
  out = out * projectionMatrix;
  out.x() = std::floor((out.x() + 1) * 0.5 * pixelWidth); 
  out.y() = std::floor((1 - (out.y() + 1) * 0.5) * pixelHeight); 
}