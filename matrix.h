#pragma once

#include <cstdlib>
#include <iostream>
#include "util.h"
#include "vector.h"

template <size_t WIDTH, size_t HEIGHT>
class Mat
{
public:
  Mat();
  Vec<WIDTH> &operator[](size_t i);

protected:
  Vec<WIDTH> rows[HEIGHT];
};