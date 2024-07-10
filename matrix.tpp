#include "matrix.h"

template <typename T, size_t WIDTH, size_t HEIGHT>
Mat<T, WIDTH, HEIGHT>::Mat(){};

template <typename T, size_t WIDTH, size_t HEIGHT>
Mat<T, WIDTH, HEIGHT>::Mat(Vec<T, WIDTH> rows[HEIGHT]){
  this->rows = rows;
};

template <typename T, size_t WIDTH, size_t HEIGHT>
Vec<T, WIDTH> &Mat<T, WIDTH, HEIGHT>::operator[](size_t i)
{
  return rows[i];
};

template <typename T, size_t WIDTH, size_t HEIGHT>
const Vec<T, WIDTH> &Mat<T, WIDTH, HEIGHT>::operator[](size_t i) const
{
  return rows[i];
};

template <typename T, size_t WIDTH, size_t HEIGHT>
Vec<T, HEIGHT> Mat<T, WIDTH, HEIGHT>::col(size_t i)
{
  Vec<T, HEIGHT> out;
  for (int r = 0; r < HEIGHT; r++)
  {
    out[r] = rows[r][i];
  }
  return out;
}

template <typename T, size_t WIDTH, size_t HEIGHT>
template <size_t ARG_WIDTH>
Mat<T, WIDTH, ARG_WIDTH> Mat<T, WIDTH, HEIGHT>::mult(Mat<T, HEIGHT, ARG_WIDTH> &m)
{
  Mat<T, WIDTH, ARG_WIDTH> out;
  for (int r = 0; r < HEIGHT; r++)
  {
    for (int c = 0; c < WIDTH; c++) {
      out[r, c] = rows[r].cross(m.col(c));
    }
  }
  return out;
};