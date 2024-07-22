#include "geom_util.h"

Matf4 RotateAboutX(float radians)
{
  Matf4 tmp = {
      {1, 0, 0, 0},
      {0, std::cos(radians), std::sin(radians), 0},
      {0, -1 * std::sin(radians), std::cos(radians), 0},
      {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutY(float radians)
{
  Matf4 tmp = {
      {std::cos(radians), 0, -1*std::sin(radians), 0},
      {0, 1, 0, 0},
      {std::sin(radians), 0, std::cos(radians), 0},
      {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutZ(float radians)
{
  Matf4 tmp = {
      {std::cos(radians), std::sin(radians), 0, 0},
      {0, -1*std::sin(radians), std::cos(radians), 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}};
  return tmp;
}