#include <iostream>
#include "vector.h"

int main()
{
  Vec<Vec<float, 3>, 3> a = {{1, 2, 3}, {4, 0, 6}, {1, 8, 4}};
  Vec<Vec<float, 2>, 3> b = {{7, 8}, {9, 10}, {11, 12}};
  std::cout << b << std::endl;
  std::cout << inv(a) << std::endl;

  // Vec<float, 3> a = {1, 2, 3};
  // Vec<Vec<float, 3>, 3> b = {{1, 2, 3}, {0, 3, 1}, {4, 5, 2}};
  // std::cout << matmul(b, b) << std::endl;
}