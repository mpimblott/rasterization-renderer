#pragma once

#include <cstdlib>
#include <iostream>
#include "util.h"
#include "vector.h"

template <typename T, size_t WIDTH, size_t HEIGHT>
class Mat
{
public:
  Mat();
  Vec<T, WIDTH> &operator[](size_t i);
  Mat<T, WIDTH, ARG_WIDTH> mult(Mat<T, HEIGHT, ARG_WIDTH> &m);
  Vec<T, HEIGHT> col(size_t i);

protected:
  Vec<T, WIDTH> rows[HEIGHT];
};

#include "matrix.cpp"