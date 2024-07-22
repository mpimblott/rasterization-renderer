#include "vector.h"

template <typename T, size_t N>
Vec<T, N>::Vec(const T (&data)[N])
{ // brackets to pass ref to array, rather than array of references
  for (unsigned int i = 0; i < N; i++)
  {
    this->data[i] = data[i];
  }
}

// template <typename T, size_t N>
// Vec<T, N>::Vec(const Vec<T, N> &data)
// { // brackets to pass ref to array, rather than array of references
//   for (unsigned int i = 0; i < N; i++)
//   {
//     this->data[i] = data[i];
//   }
// }
template <typename T, size_t N>
Vec<T, N>::Vec(const std::array<T, N> data)
{
  for (unsigned int i = 0; i < N; i++)
  {
    this->data[i] = data[i];
  } 
}

template <typename T, size_t N>
Vec<T, N>::Vec(std::initializer_list<T> v)
{
  assert(v.size() == N && "Vector initialzer list has incorrect size.");
  std::copy(v.begin(), v.end(), data.begin());
}

template <typename T, size_t N>
size_t Vec<T, N>::len()
{
  return N;
}

template <typename T, size_t N>
T &Vec<T, N>::operator[](size_t i)
{
  assert(i < N && "Accessing outside of vector bounds.");
  return data[i];
}

template <typename T, size_t N>
const T &Vec<T, N>::operator[](size_t i) const
{
  assert(i < N && "Accessing outside of vector bounds.");
  return data[i];
}

template <typename T, size_t N>
bool Vec<T, N>::operator==(const Vec<T, N> &v)
{
  bool same = true;
  for (size_t i = 0; i < N; i++)
  {
    if (data[i] != v[i])
    {
      same = false;
    }
  }
  return same;
}


template <typename T, size_t N>
Vec<T, N> &Vec<T, N>::operator=(const Vec<T, N> &v)
{
  for (size_t i = 0; i < N; i++)
  {
    data[i] = v[i];
  }
  return *this;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator+(const Vec<T, N> &v) const
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
    out[i] = data[i] + v[i];
  return out;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator-(const Vec<T, N> &v) const
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
    out[i] = data[i] - v[i];
  return out;
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const Vec<T, N> &v)
{
  os << "[";
  for (size_t i = 0; i < N; i++)
  {
    os << v[i];
    if (i < N - 1)
      os << ", ";
  }
  os << "]";
  return os;
}

template <typename Y, size_t M, size_t U>
std::ostream &operator<<(std::ostream &os, const Vec<Vec<Y, M>, U> &m)
{
  os << "[";
  for (size_t r = 0; r < U; r++)
  { 
    if (r > 0)
      os << " ";
    os << m[r];
    if (r < U - 1)
      os << "\n";
  }
  os << "]";
  return os;
}

template <typename T, size_t N>
Vec<T, N> operator*(typename V_traits<T>::element_type lhs, const Vec<T, N> &rhs)
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
    out[i] = lhs * rhs[i];
  return out;
}

template <typename T, size_t N>
Vec<T, N> operator*(const Vec<T, N> &lhs, typename V_traits<T>::element_type rhs)
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
    out[i] = rhs * lhs[i];
  return out;
}

template <typename T, size_t N>
Vec<T, N> operator/(const Vec<T, N> & lhs, typename V_traits<T>::element_type rhs)
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
  {
    out[i] = lhs[i] / rhs;
  }
  return out;
}

template <typename Y, size_t M, size_t U>
Vec<Vec<Y, U>, M> operator/(const Vec<Vec<Y, U>, M> & lhs, typename V_traits<Y>::element_type rhs)
{
  Vec<Vec<Y, U>, M> out;
  for (size_t i = 0; i < M; i++)
  {
    out[i] = lhs[i] / rhs;
  }
  return out;
}

template <typename T, size_t N>
T dot(const Vec<T, N> &lhs, const Vec<T, N> &rhs)
{
  T total = 0;
  for (size_t i = 0; i < N; i++)
    total += rhs[i] * lhs[i];
  return total;
}

template <typename T, size_t N>
T dot(const Vec<Vec<T, 1>, N> &lhs, const Vec<T, N> &rhs)
{
  T total = 0;
  for (size_t i = 0; i < N; i++)
    total += rhs[i] * lhs[i];
  return total;
}

// left multiplying by a row vector
template <typename Y, size_t M, size_t U>
Vec<Y, M> operator*(const Vec<Y, U> &lhs, const Vec<Vec<Y, M>, U> &rhs)
{
  Vec<Y, M> out;
  for (size_t c = 0; c < M; c++)
  {
    Y t = 0;
    for (size_t r = 0; r < U; r++)
    {
      t += lhs[r] * rhs[r][c];
    }
    out[c] = t;
  }
  return out;
}

// right multiplying by a column vector
template <typename Y, size_t M, size_t U>
Vec<Vec<Y, 1>, M> operator*(const Vec<Vec<Y, U>, M> &lhs, const Vec<Vec<Y, 1>, U> &rhs)
{
  Vec<Y, U> tmp = transpose(rhs);
  Vec<Vec<Y, 1>, M> out;
  for (size_t r = 0; r < M; r++)
  {
    Y tot = 0;
    out[r][0] = dot(lhs[r], tmp);
  }
  return out;
}

// MxU * UxP
template <typename Y, size_t M, size_t U, size_t P>
Vec<Vec<Y, P>, M> operator*(const Vec<Vec<Y, U>, M> &lhs, const Vec<Vec<Y, P>, U> &rhs)
{
  Vec<Vec<Y, U>, P> tmp = transpose(rhs);
  Vec<Vec<Y, P>, M> out;
  for (size_t c = 0; c < P; c++)
  {
    for (size_t r = 0; r < M; r++)
    {
      Y tot = 0;
      out[r][c] = dot(lhs[r], tmp[c]);
    }
  }
  return out;
}

template <typename T, size_t N>
T minor(const Vec<Vec<T, N>, N> &m, size_t col, size_t row)
{
  Vec<Vec<T, N - 1>, N - 1> tmp;
  size_t dst_row = 0;
  size_t dst_col = 0;
  for (size_t c = 0; c < N; c++)
  {
    dst_row = 0;
    if (c == col)
      continue;
    for (size_t r = 0; r < N; r++)
    {
      if (r == row)
        continue;
      tmp[dst_col][dst_row] = m[c][r];
      dst_row += 1;
    }
    dst_col += 1;
  }
  return det(tmp);
}

template <typename T, size_t N>
T cofactor(const Vec<Vec<T, N>, N> &m, size_t col, size_t row)
{
  return std::pow(-1, col + row) * minor(m, col, row);
}

template <typename T>
T det(const Vec<Vec<T, 2>, 2> &m)
{
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <typename T>
T det(const Vec<Vec<T, 3>, 3> &m)
{
  // using sarru's rule
  return m[0][0] * m[1][1] * m[2][2] +
         m[0][1] * m[1][2] * m[2][0] +
         m[0][2] * m[1][0] * m[2][1] -
         m[2][0] * m[1][1] * m[0][2] -
         m[2][1] * m[1][2] * m[0][0] -
         m[2][2] * m[1][0] * m[0][1];
}

template <typename T, size_t N>
T det(const Vec<Vec<T, N>, N> &m)
{
  const size_t c = 0;
  T total = 0;
  for (size_t r = 0; r < N; r++)
  {
    total += m[c][r] * cofactor(m, 0, r);
  }
  return total;
}

template <typename T, size_t N>
Vec<Vec<T, 1>, N> transpose(const Vec<T, N> &v)
{
  Vec<Vec<T, 1>, N> out;
  for (size_t i = 0; i < N; i++)
  {
    out[i][0] = v[i];
  }
  return out;
}

template <typename T, size_t N>
Vec<T, N> transpose(const Vec<Vec<T, 1>, N> &m)
{
  Vec<T, N> out;
  for (size_t i = 0; i < N; i++)
  {
    out[i] = m[i][0];
  }
  return out;
}

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> transpose(const Vec<Vec<T, M>, N> &m)
{
  Vec<Vec<T, N>, M> out;
  for (size_t i = 0; i < N; i++)
  {
    for (size_t j = 0; j < M; j++)
    {
      out[j][i] = m[i][j];
    }
  }
  return out;
}

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> adjoint(Vec<Vec<T, M>, N> &m)
{
  Vec<Vec<T, N>, M> out;
  auto transp = transpose(m);
  for (size_t c = 0; c < N; c++)
  {
    for (size_t r = 0; r < M; r++)
    {
      out[c][r] = cofactor(transp, c, r);
    }
  }
  return out;
}

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> adjoint(const Vec<Vec<T, M>, N> &m)
{
  Vec<Vec<T, N>, M> out;
  auto transp = transpose(m);
  for (size_t c = 0; c < N; c++)
  {
    for (size_t r = 0; r < M; r++)
    {
      out[c][r] = cofactor(transp, c, r);
    }
  }
  return out;
}

template <typename T, size_t N, size_t M>
Vec<Vec<T, N>, M> inv(const Vec<Vec<T, M>, N> &m)
{
  return adjoint(m) / det(m);
}

template <typename T, size_t N>
T Vec<T, N>::norm() const
{
  T tot = 0;
  for (T const&i: data)
  {
    tot += pow(i, 2);
  }
  return sqrt(tot);
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::unit() const
{
  Vec<T, N> out(this->data);
  return (out / norm());
}

template <typename T, size_t N>
Vec<T, N> &ZeroVec(Vec<T, N> &v)
{
  for (size_t i = 0; i < N; i++)
  {
    v[i] = 0;
  }
  return v;
}

template <typename Y, size_t M, size_t U>
Vec<Vec<Y, U>, M> &ZeroVec(Vec<Vec<Y, U>, M> &v)
{
  for (size_t i = 0; i < M; i++)
  {
    ZeroVec(v[i]);
  } 
  return v;
}

template <typename Y, size_t M, size_t U>
Vec<Vec<Y, U>, M> &Id(Vec<Vec<Y, U>, M> &v)
{
  for (size_t r = 0; r < M; r++)
  {
    for (size_t c = 0; c < U; c++)
    {
      if (c == r)
      {
        v[r][c] = 1;
      } else {
        v[r][c] = 0;
      }
    }
  }
  return v;
}

template <typename Y, size_t M, size_t U, size_t J>
Vec<Vec<Vec<Y, J>, U>, M>  &Id(Vec<Vec<Vec<Y, J>, U>, M> &v)
{
  for (size_t i = 0; i < M; i++)
  {
    Id(v[i]);
  }
  return v;
}