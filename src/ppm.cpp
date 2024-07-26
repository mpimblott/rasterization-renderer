#include "ppm.h"

void write_color(std::ostream &out, Color pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // translate the [0,1] color to uint8 for each component
  out << static_cast<int>(256 * r) << ' ' << static_cast<int>(256 * g) << ' '
      << static_cast<int>(256 * b) << '\n';
}