#include <iostream>
#include "vector.h"
#include "point.h"
#include "geometry.h"
#include "camera.h"
#include "geom_util.h"

  // Matf4 ltw = { {0.718762, 0.615033, -0.324324, 0},
  //               {-0.393732, 0.744416, 0.539277, 0},
  //               {0.573042, -0.259959, 0.777216, 0},
  //               {0.526967, 1.254234, -2.532150, 1} };
  // Point3h c = {-0.5, 0.5, -0.5};
int main()
{
  // Matf4 camMove = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 2, 1}};
  std::vector<Point3h> vertices = {{0, 2, -5}, {0, 0, -5}, {1, 0, -5}};
  std::cout << vertices[2] << std::endl;
  std::vector<size_t> indices = {0, 2, 1, 0}; 
  Mesh triangle(vertices, indices);
  std::cout << triangle << std::endl;
  Camera cam(4, 4, 500, 500);
  Point3h test_point = Point3h(0.1, 0.1, -5);
  std::cout << triangle.test_point(test_point) << std::endl;
}