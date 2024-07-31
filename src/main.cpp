#include <iostream>
#include <memory>

#include "camera.h"
#include "geom_util.h"
#include "geometry.h"
#include "point.h"
#include "vector.h"
#include "obj.h"

using std::shared_ptr;

#define WIDTH 700
#define HEIGHT 700

int main() {
    Camera cam(WIDTH, HEIGHT, 90, 1, 100);

    ppmRenderer renderer;
    ObjLoader loader;
    // shared_ptr<Mesh> mesh = objLoader("/home/matt/projects/rasterization-renderer/meshes/cube.obj");
    shared_ptr<Mesh> mesh = loader.load("/home/matt/projects/rasterization-renderer/meshes/shuttle.obj");
    std::cerr << (*mesh) << std::endl;
    cam.set_look_at(Point3h(-3, -8, 8), Vec3h(0, 0, 0), Point3h(0, 1, 0));
    std::vector<float> img_buffer = cam.build_img_buffer(*mesh);
    renderer.render(WIDTH, HEIGHT, img_buffer);
}