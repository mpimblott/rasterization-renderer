#pragma once

#include <cstdlib>
#include <array>
#include <iostream>
#include <cassert>
#include <cmath>
#include <tuple>
#include <utility>
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

// template <typename T, size_t N>
// struct V_shape
// {
//   using dimensions = std::tuple<size_t>;
//   constexpr dimensions get_dim() {return std::make_tuple(N);}
// };

// template <typename T, size_t N, size_t M>
// struct V_shape<Vec<T, N>, M>
// {
//   using inner_dim = typename V_shape<T, N>::dimensions;
//   using dimensions = decltype(std::tuple_cat(std::make_tuple(M), inner_dim()));
//   constexpr dimensions get_dim() {
//     return std::tuple_cat(std::make_tuple(M), V_shape<T, N>::get_dim());
//   }
// };

void print_tuple(const std::tuple<size_t> &t)
{
  std::cout << std::get<0>(t);
}

// template <typename T, size_t N, size_t M>
// void print_dimensions(const Vec<Vec<T, N>, M> &m) 
// {
//   auto dims = V_shape<Vec<T, N>, M>().get_dim();
//   std::cout << "Dimensions: ";
//   print_tuple(dims);
//   std::cout << std::endl;
// }

// declare friend function templates
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const Vec<T, N> &v);

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const Vec<Vec<T, N>, N> &m);

template <typename T, size_t N>
Vec<T, N> operator*(typename V_traits<T>::element_type lhs, const Vec<T, N> &rhs);

template <typename T, size_t N>
Vec<T, N> operator*(const Vec<T, N> &lhs, typename V_traits<T>::element_type rhs);

template <typename T, size_t N>
Vec<T, N> operator/(const Vec<T, N> & lhs, typename V_traits<T>::element_type rhs);

// template <typename T, size_t N>
// Vec<Vec<T, N>, N> operator/(const Vec<Vec<T, N>, N> & lhs, typename V_traits<T>::element_type rhs);

template <typename T, size_t N>
T dot(const Vec<T, N> &lhs, const Vec<T, N> &rhs);

template <typename T, size_t N, size_t M>
T dot(const Vec<Vec<T, 1>, N> &lhs, const Vec<T, N> &rhs);

template <typename T, size_t N, size_t M>
Vec<T, M> matmul(const Vec<Vec<T, M>, N> &lhs, const Vec<T, N> &rhs);

template <typename T, size_t N, size_t M, size_t P>
Vec<T, M> matmul(const Vec<Vec<T, M>, N> &lhs, const Vec<Vec<T, N>, M> &rhs);

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

// rows, cols
template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> transpose(const Vec<Vec<T, M>, N> &m);

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> adjoint(Vec<Vec<T, M>, N> &m);

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> inv(Vec<Vec<T, M>, N> &m);

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
  friend std::ostream &operator<< <>(std::ostream &os, const Vec<T, N> &v);
  friend std::ostream &operator<< <>(std::ostream &os, const Vec<Vec<T, N>, N> &m);
  friend Vec<T, N> operator* <>(typename V_traits<T>::element_type lhs, const Vec<T, N> &rhs);
  friend Vec<T, N> operator* <>(const Vec<T, N> &lhs, typename V_traits<T>::element_type rhs);
  friend Vec<T, N> operator/ <>(const Vec<T, N> & lhs, typename V_traits<T>::element_type rhs);
  // friend Vec<Vec<T, N>, N> operator/ <>(const Vec<Vec<T, N>, N> & lhs, typename V_traits<T>::element_type rhs);
  // friend T dot<>(const Vec<T, N> &lhs, const Vec<T, N> &rhs);
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
typedef Vec<Vec<Vec<float, 2>, 2>, 2> D3Arrf2;

const Vec<Vec<float, 2>, 2> I2 = {{1, 0}, {0, 1}};
const Vec<Vec<float, 3>, 3> I3 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

#include "vector.tpp"