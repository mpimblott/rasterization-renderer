#include <iostream>
#include "vector.h"
#include "matrix.h"

int main()
{
  Vec3 veca;
  Vec3 vecb;
  veca.x = 1.0f;
  std::cout << veca + vecb << std::endl;

  Mat<float, 2, 2> mat;
  std::cout << mat << std::endl;
}