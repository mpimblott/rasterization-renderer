#include "camera.h"
#include "geom_util.h"
#include "geometry.h"
#include "point.h"
#include "vector.h"
#include <iostream>
#include <memory>

using std::shared_ptr;

// Matf4 ltw = { {0.718762, 0.615033, -0.324324, 0},
//               {-0.393732, 0.744416, 0.539277, 0},
//               {0.573042, -0.259959, 0.777216, 0},
//               {0.526967, 1.254234, -2.532150, 1} };
// Point3h c = {-0.5, 0.5, -0.5};
int main() {
  // Matf4 camMove = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 2, 1}};
  Camera cam(500, 500, 90, 40, 120);
  // Mesh triangle({{-0.5, 0.5, -2}, {-0.5, -0.5, -2}, {0.5, -0.5, -2}}, {0, 1,
  // 2, 0}); std::cout << triangle << std::endl;

  // cam.build_img_buffer(triangle);
  ppmRenderer renderer;
  shared_ptr<Mesh> mesh = loadGeoFile(
      "/home/matt/projects/rasterization-renderer/triangle_single.mesh");
  std::cerr << (*mesh) << std::endl;
  std::vector<float> img_buffer = cam.build_img_buffer(*mesh);
  renderer.render(500, 500, img_buffer);
}