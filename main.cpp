#include <iostream>
#include "vector.h"
#include "matrix.h"

int main()
{
  Vec2 veca({1.0f, 2.0f});
  Vec2 vecb= {3.0f, 4.0f};
  std::cout << veca << std::endl;

  Mat<float, 2, 2> mat = {
      Vec2({1.0f, 2.0f}),
      Vec2({3.0f, 4.0f})
  };
  Mat<float, 2, 2> mat2 = {
      veca,
      vecb
  };
  std::cout << mat2.mult(mat) << std::endl;

  Vec2 vec2a = {1.0f, 2.0f};
  Vec2 vec2b = {3.0f, 4.0f};
  vec2a.x = 5;
  std::cout << vec2a << std::endl;
}