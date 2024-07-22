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
  void setPos();
  void setLookat();
  Point3 getPos() const;
  Vec3 getLookat() const;
  Camera &transform(Matf4 &m);
  Point3h zDivide(Point3h &point) const;
  Point3h screenToRaster(Point3h &point);

private:
  void init();
  Matf4 camMat;
  float viewportWidth;
  float viewportHeight;
  size_t pixelsX;
  size_t pixelsY;
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
