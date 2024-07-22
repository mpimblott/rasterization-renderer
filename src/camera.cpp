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
  ZeroVec(camMat);
}

Matf4 Camera::wld2cam() const
{
  return camMat;
}

Matf4 Camera::cam2wld() const
{
  return inv(camMat);
}

Camera &Camera::transform(Matf4 &m)
{
  camMat = camMat * m;
  return *this;
}

Point3h Camera::zDivide(Point3h &point) const
{
  Point3h out;
  out.x = point.x / (-1 * point.z);
  out.y = point.y / (-1 * point.z);
  return out;
}

/*
  normalise the x and y coordinates in screen space to raster space
  (width and height limited by fov and rounded)
*/
Point3h Camera::screenToRaster(Point3h &point)
{
  float normalised_x = (point.x + (viewportWidth / 2)) / viewportWidth;
  float normalised_y = (point.y + (viewportHeight / 2)) / viewportHeight;
  std::cout << normalised_x << std::endl;
  std::cout << normalised_y << std::endl;
  return Point3h(std::floor(normalised_x * pixelsX), std::floor((1 - normalised_y) * pixelsY), point[2]);
}

void ppmRenderer::render(size_t width, size_t height)
{
  // first line of the image file
  std::cout << "P3\n"
            << width << ' ' << height << "\n255\n";
  for (int j = 0; j < height; ++j)
  {
    std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
    for (int i = 0; i < width; ++i)
    {
      Color pixel_color(0, 0, 0);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                       \n";
}