#pragma once

#include <cstdlib>
#include <array>
#include <iostream>
#include <cassert>
#include <cmath>
#include "util.h"

template <typename T, size_t N>
class Vec;

/*
element_type is alias for T - recursive base case when V_traits is instantiated
with a non-vector type
*/
template <typename T>
struct V_traits
{
  typedef T element_type;
};

/*
partial template specialisation fo the case of a vector type
compiler chooses the most specialised matching template
*/
template <typename T, size_t N>
struct V_traits<Vec<T, N>>
{
  typedef typename V_traits<T>::element_type element_type;
};

// declare friend function templates
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const Vec<T, N> &v);

template <typename T, size_t N>
Vec<T, N> operator*(typename V_traits<T>::element_type lhs, const Vec<T, N> &rhs);

template <typename T, size_t N>
Vec<T, N> operator*(const Vec<T, N> &lhs, typename V_traits<T>::element_type rhs);

template <typename T, size_t N>
T dot(const Vec<T, N> &lhs, const Vec<T, N> &rhs);

template <typename T, size_t N, size_t M>
Vec<T, M> matmul(const Vec<Vec<T, M>, N> &lhs, const Vec<T, N> &rhs);

template <typename T, size_t N>
T minor(const Vec<Vec<T, N>, N> &m, size_t col, size_t row);

template <typename T, size_t N>
T cofactor(const Vec<Vec<T, N>, N> &m, size_t col, size_t row);

template <typename T>
T det(const Vec<Vec<T, 2>, 2> &m);

template <typename T>
T det(const Vec<Vec<T, 3>, 3> &m);

template <typename T, size_t N>
T det(const Vec<Vec<T, N>, N> &m);

template <typename T, size_t N>
Vec<Vec<T, 1>, N> transpose(const Vec<T, N> &v);

template <typename T, size_t N>
Vec<T, N> transpose(Vec<Vec<T, 1>, N> &m);

// cols, rows
template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> transpose(const Vec<Vec<T, M>, N> &m);

template <typename T, size_t N>
class Vec
{
public:
  Vec() = default;
  Vec(const T (&data)[N]);
  Vec(std::initializer_list<T> data);
  // explicit Vec(const Vec<T, N> &data);
  T &operator[](size_t i);
  const T &operator[](size_t i) const;
  size_t len();
  Vec<T, N> operator+(const Vec<T, N> &v) const;
  Vec<T, N> operator-(const Vec<T, N> &v) const;
  // add <> to indicate referring to template function, but parameters should be deduced from environment
  friend std::ostream &operator<< <>(std::ostream &os, const Vec<T, N> &v);
  friend Vec<T, N> operator* <>(typename V_traits<T>::element_type lhs, const Vec<T, N> &rhs);
  friend Vec<T, N> operator* <>(const Vec<T, N> &lhs, typename V_traits<T>::element_type rhs);
  friend T dot<>(const Vec<T, N> &lhs, const Vec<T, N> &rhs);
  // Height, Width (rows, cols)
  // friend Vec<T, N> matmul<>(const Vec<Vec<T, N>, N> &lhs, const Vec<T, N> &rhs);

private:
  std::array<T, N> data;
};

typedef Vec<float, 2> Vecf2;
typedef Vec<float, 3> Vecf3;
typedef Vec<Vec<float, 2>, 2> Matf2;
typedef Vec<Vec<float, 3>, 3> Matf3;
typedef Vec<Vec<float, 4>, 4> Matf4;

const Vec<Vec<float, 2>, 2> I2 = {{1, 0}, {0, 1}};
const Vec<Vec<float, 3>, 3> I3 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

#include "vector.tpp"