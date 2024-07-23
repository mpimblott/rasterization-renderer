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

Point3h &Camera::camToScreen(Point3h &point)
{
  point.x() = point.x() / (-1 * point.z());
  point.y() = point.y() / (-1 * point.z());
  point.z() = -1 * point.z();
  return point;
}

/*
  normalise the x and y coordinates in screen space to raster space
  (width and height limited by fov and rounded)
*/
Point3h &Camera::screenToRaster(Point3h &point)
{
  float normalised_x = (point.x() + (viewportWidth / 2)) / viewportWidth;
  float normalised_y = (point.y() + (viewportHeight / 2)) / viewportHeight;
  point.x() = std::floor(normalised_x * pixelsX);
  point.y() = std::floor((1 - normalised_y) * pixelsY);
  return point;
}

/*
* compute the raster coordinate of a world coordinate
*/
Point3h &Camera::computePixelCoordinate(Point3h &point)
{
  camToScreen(point);
  screenToRaster(point);
  return point;
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