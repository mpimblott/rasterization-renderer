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
  Camera cam(500, 500, 90, 1, 3);
  Mesh triangle({{-0.5, 0.5, -2}, {-0.5, -0.5, -2}, {0.5, -0.5, -2}}, {0, 1, 2, 0});
  // std::cout << triangle << std::endl;
  MeshList world;
  world.add(std::make_shared<Mesh>(triangle));

  cam.build_buffer(triangle);
  ppmRenderer renderer;
  renderer.render(500, 500, cam.get_buffer());
}