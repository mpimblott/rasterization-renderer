#include "vector.h"

template <size_t SIZE>
Vec<SIZE>::Vec()
{
  for (size_t i = 0; i < SIZE; i++)
    data[i] = 0.0f;
}

template <size_t SIZE>
size_t Vec<SIZE>::len() {
  return SIZE;
}

template <size_t SIZE>
float &Vec<SIZE>::operator[](size_t i){
  return data[i];
}

template <size_t SIZE>
const float &Vec<SIZE>::operator[](size_t i) const {
  return data[i];
}

template <size_t SIZE>
Vec<SIZE> Vec<SIZE>::operator+(Vec<SIZE> &v) {
  Vec<SIZE> out;
  for (size_t i = 0; i < SIZE; i++)
    out[i] = data[i] + v[i];
  return out;
}

template class Vec<2>;
template class Vec<3>;
