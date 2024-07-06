#include "matrix.h"

template <typename T, size_t WIDTH, size_t HEIGHT>
Mat<T, WIDTH, HEIGHT>::Mat() {};

template <typename T, size_t WIDTH, size_t HEIGHT>
Vec<T, WIDTH> &Mat<T, WIDTH, HEIGHT>::operator[](size_t i) {
  return rows[i];
};

template <typename T, size_t WIDTH, size_t HEIGHT>
Vec<T, HEIGHT> Mat<T, WIDTH, HEIGHT>::col(size_t i) {

} 

template <typename T, size_t WIDTH, size_t HEIGHT, size_t ARG_WIDTH>
Mat<T, WIDTH, ARG_WIDTH> mult(mat<T, HEIGHT, ARG_WIDTH> &m) {

};