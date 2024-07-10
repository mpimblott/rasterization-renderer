#include "vector.h"
#include "matrix.h"

int main()
{
  Vec3 veca;
  Vec3 vecb;
  veca.x = 1.0f;
  std::cout << veca + vecb << std::endl;

  // Mat<float, 2, 2> mat({
  //   Vec<float, 2>({1.0f, 2.0f}),
  //   Vec<float, 2>({3.0f, 4.0f})
  // });
  // std::cout << mat << std::endl;
  Vec<float, 2> v1 = {1.0f};
  std:: cout << v1 << std::endl;
  int a[3] = {1,2};
  std::cout << *a << std::endl;
}