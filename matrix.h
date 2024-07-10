#pragma once

#include <cstdlib>
#include <iostream>
#include "util.h"
#include "vector.h"

/*
 * A matrix of dimension d = 2.
 */
template <typename T, size_t WIDTH, size_t HEIGHT>
class Mat
{
public:
  Mat();
  Mat(Vec<T, WIDTH> rows[HEIGHT]);
  // Mat(std::initializer_list<Vec<T, WIDTH>> rows) : Mat(rows) {}
  Vec<T, WIDTH> &operator[](size_t i);
  const Vec<T, WIDTH> &operator[](size_t i) const;
  Vec<T, HEIGHT> col(size_t i);
  template <size_t ARG_WIDTH>
  Mat<T, WIDTH, ARG_WIDTH> mult(Mat<T, HEIGHT, ARG_WIDTH> &m);
  friend std::ostream &operator<<(std::ostream &os, const Mat<T, WIDTH, HEIGHT> &v)
  {
    os << "[";
    for (size_t i = 0; i < HEIGHT; i++)
    {
      os << v[i];
      if (i < HEIGHT - 1)
        os << ", " << std::endl;
    }
    os << "]";
    return os;
  }

protected:
  Vec<T, WIDTH> rows[HEIGHT];
};

#include "matrix.tpp"