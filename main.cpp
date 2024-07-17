#include <iostream>
#include "vector.h"
#include "geometry.h"

int main()
{
  Matf4 ltw = { {0.718762, 0.615033, -0.324324, 0},
                {-0.393732, 0.744416, 0.539277, 0},
                {0.573042, -0.259959, 0.777216, 0},
                {0.526967, 1.254234, -2.532150, 1} };
  Point3h c = {-0.5, 0.5, -0.5};
  std::cout << c * ltw << std::endl;
}