#include "matrix.h"

template <size_t WIDTH, size_t HEIGHT>
Mat<WIDTH, HEIGHT>::Mat() {};

template <size_t WIDTH,size_t HEIGHT>
Vec<WIDTH> &Mat<WIDTH, HEIGHT>::operator[](size_t i) {
  return rows[i];
};