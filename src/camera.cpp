#include "camera.h"

Camera::Camera(float viewportWidth, float viewportHeight, size_t pixelsX, size_t pixelsY)
{
  this->viewportWidth = viewportWidth;
  this->viewportHeight = viewportHeight;
  this->pixelsX = pixelsX;
  this->pixelsY = pixelsY;
  init();
}

void Camera::init()
{
  Id(camMat);
  std::vector<float> tmp(pixelsX * pixelsY * 3);
  imgBuffer = tmp;
}

Matf4 Camera::wld2cam() const
{
  return camMat;
}

Matf4 Camera::cam2wld() const
{
  return inv(camMat);
}

void Camera::setPos(Point3 &p)
{
  // build the translation matrix from the default position to the desired point
  camMat[3][0] = p[0] - defaultPos[0];
  camMat[3][1] = p[1] - defaultPos[1];
  camMat[3][2] = p[2] - defaultPos[2];
}

Point3 Camera::getPos() const
{
  return Point3(camMat[3][0], camMat[3][1], camMat[3][2]);
}

void Camera::setLookat(Point3 &v)
{
  Point3 pos = getPos();
  Vec<float, 3> lookatVector = v - pos;
}

Point3h &Camera::camToScreen(const Point3h &src_pt, Point3h &dst_pt) const
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
Point3h &Camera::screenToRaster(const Point3h &src_pt, Point3h &dst_pt) const
{
  float normalised_x = (src_pt.x() + (viewportWidth / 2)) / viewportWidth;
  float normalised_y = (src_pt.y() + (viewportHeight / 2)) / viewportHeight;
  dst_pt.x() = std::floor(normalised_x * pixelsX);
  dst_pt.y() = std::floor((1 - normalised_y) * pixelsY);
  return dst_pt;
}

/*
 * compute the raster coordinate of a world coordinate
 */
Point3h &Camera::computePixelCoordinate(const Point3h &src_pt, Point3h &dst_pt) const
{
  camToScreen(src_pt, dst_pt);
  screenToRaster(dst_pt, dst_pt);
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
    computePixelCoordinate(vertex, p);
    projection.add_vertex(p);
  }
  return projection;
}

void Camera::build_buffer(Mesh &mesh)
{
  Mesh projection = build_projection(mesh);
  // std::cout << projection << std::endl;
  for (size_t y = 0; y < pixelsY; y++)
  {
    for (size_t x = 0; x < pixelsX; x++)
    {
      size_t idx = y * pixelsY * 3 + 3 * x;
      if (test_point(x, y, projection))
      {
        imgBuffer[idx] = 1.0;
        // std::cout << "true" << std::endl;
      } else {
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
