#pragma once

#include "vector.h"
#include "point.h"
#include "math.h"
#include "ppm.h"

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
  Point3h &camToScreen(Point3h &point);
  Point3h &screenToRaster(Point3h &point);
  Point3h &computePixelCoordinate(Point3h &point);

private:
  void init();
  Matf4 camMat;
  float viewportWidth;
  float viewportHeight;
  size_t pixelsX;
  size_t pixelsY;
  Point3h defaultPos = Point3h(0, 0, 0);
};

class Renderer
{
public:
  Renderer() = default;
  ~Renderer() = default;
  virtual void render(size_t width, size_t height) = 0;
};

class ppmRenderer: public Renderer {
public:
  void render(size_t width, size_t height) override;
};
