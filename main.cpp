#include <iostream>
#include "vector.h"

int main()
{
  Vecf2 a = {1, 3};
  Vecf2 b = {3, 4};
  Matf3 c = {{0, 3, 3}, {3, 4, 6}, {9, 3, 3}};
  Matf2 d = {{1, 3}, {4, 2}};
  Matf4 e = {{0, 3, 3, 1}, {3, 10, 6, 2}, {9, 3, 3, 4}, {10, 3, 3, 1}};
  // std::cout << I3 <<std::endl;
  // std::cout << matmul(d, b) << std::endl;
  // auto m = minor(c, 1, 1);
  // std::cout << det(c) << std::endl;
  // std::cout << e << std::endl;
  // std::cout << det(e) << std::endl;
  // std::cout << e << std::endl;
  // Vec<Vec<float, 1>, 2> f = {{0}, {1}};
  // std::cout << f << std::endl;
  // std::cout << f << std::endl;
  // std::cout << transpose(f) << std::endl;
  // Matf3 A = {{1, 3, -1}, {-2, 1, 2}, {0, 5, 3}};
  // std::cout << A << std::endl;
  // std::cout << transpose(A) << std::endl;
  // std::cout << adjoint(A) << std::endl;
  std::cout << c << std::endl;
}