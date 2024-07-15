// Emacs mode -*-c++-*- //
#ifndef _FM_VECTOR_H_
#define _FM_VECTOR_H_
/*
 * NAME: FM_vector.h
 *
 * WRITTEN BY:
 * Patrick Moran pmoran@nas.nasa.gov
 */
#include <iostream>
#include <math.h>
#ifndef FM_COORD
#define FM_COORD
typedef float FM_coord;
#endif
template <int N, typename T>
class FM_vector;
template <typename T>
struct FM_traits
{
  typedef T element_type;
};
template <int N, typename T>
struct FM_traits<FM_vector<N, T>>
{
  typedef typename FM_traits<T>::element_type element_type;
};
template <int N, typename T>
T FM_dot(const FM_vector<N, T> &, const FM_vector<N, T> &);
template <typename T>
FM_vector<3, T> FM_cross(const FM_vector<3, T> &, const FM_vector<3, T> &);
template <int N, typename T = FM_coord>
class FM_vector
{
public:
  FM_vector() {}
  FM_vector(const T dat[])
  {
    for (int i = 0; i < N; i++)
      d[i] = dat[i];
  }
  template <typename S>
  explicit FM_vector(const FM_vector<N, S> &dat)
  {
    for (int i = 0; i < N; i++)
      d[i] = (T)dat[i];
  }
  T &operator[](int i) { return d[i]; }
  const T &operator[](int i) const { return d[i]; }
  operator const T *() const
  {
    return (typename FM_traits<T>::element_type *)d;
  }
  friend bool operator==(const FM_vector<N, T> &lhs,
                         const FM_vector<N, T> &rhs)
  {
    12 bool res = true;
    for (int i = 0; i < N; i++)
    {
      if (!(lhs[i] == rhs[i]))
      {
        res = false;
        break;
      }
    }
    return res;
  }
  FM_vector<N, T> &operator+=(const FM_vector<N, T> &v)
  {
    for (int i = 0; i < N; i++)
      d[i] += v[i];
    return *this;
  }
  FM_vector<N, T> &operator-=(const FM_vector<N, T> &v)
  {
    for (int i = 0; i < N; i++)
      d[i] -= v[i];
    return *this;
  }
  FM_vector<N, T> &operator*=(typename FM_traits<T>::element_type s)
  {
    for (int i = 0; i < N; i++)
      d[i] *= s;
    return *this;
  }
  FM_vector<N, T> &operator/=(typename FM_traits<T>::element_type s)
  {
    for (int i = 0; i < N; i++)
      d[i] /= s;
    return *this;
  }
  friend FM_vector<N, T> operator-(const FM_vector<N, T> &u)
  {
    T tmp[N];
    for (int i = 0; i < N; i++)
      tmp[i] = -u[i];
    return FM_vector<N, T>(tmp);
  }
  friend FM_vector<N, T> operator+(const FM_vector<N, T> &lhs,
                                   const FM_vector<N, T> &rhs)
  {
    T tmp[N];
    for (int i = 0; i < N; i++)
      tmp[i] = lhs[i] + rhs[i];
    return FM_vector<N, T>(tmp);
  }
  friend FM_vector<N, T> operator-(const FM_vector<N, T> &lhs,
                                   const FM_vector<N, T> &rhs)
  {
    T tmp[N];
    for (int i = 0; i < N; i++)
      tmp[i] = lhs[i] - rhs[i];
    return FM_vector<N, T>(tmp);
  }
  friend FM_vector<N, T>
  operator*(typename FM_traits<T>::element_type lhs,
            const FM_vector<N, T> &rhs)
  {
    T tmp[N];
    for (int i = 0; i < N; i++)
      tmp[i] = lhs * rhs[i];
    return FM_vector<N, T>(tmp);
  }
  13 friend FM_vector<N, T>
  operator*(const FM_vector<N, T> &lhs,
            typename FM_traits<T>::element_type rhs)
  {
    T tmp[N];
    for (int i = 0; i < N; i++)
      tmp[i] = lhs[i] * rhs;
    return FM_vector<N, T>(tmp);
  }

private:
  T d[N];
};
template <typename T>
class FM_vector<1, T>
{
public:
  FM_vector() {}
  FM_vector(const T dat[])
  {
    d[0] = dat[0];
  }
  template <typename S>
  explicit FM_vector(const FM_vector<1, S> &dat)
  {
    d[0] = (T)dat[0];
  }
  FM_vector(const T &a0)
  {
    d[0] = a0;
  }
  T &operator[](int i) { return d[i]; }
  const T &operator[](int i) const { return d[i]; }
  operator const T *() const
  {
    return (typename FM_traits<T>::element_type *)d;
  }
  friend bool operator==(const FM_vector<1, T> &lhs,
                         const FM_vector<1, T> &rhs)
  {
    return lhs.d[0] == rhs.d[0];
  }
  FM_vector<1, T> &operator+=(const FM_vector<1, T> &v)
  {
    d[0] += v[0];
    return *this;
  }
  FM_vector<1, T> &operator-=(const FM_vector<1, T> &v)
  {
    d[0] -= v[0];
    return *this;
  }
  FM_vector<1, T> &operator*=(typename FM_traits<T>::element_type s)
  {
    d[0] *= s;
    return *this;
  }
  FM_vector<1, T> &operator/=(typename FM_traits<T>::element_type s)
  {
    d[0] /= s;
    return *this;
    14
  }
  friend FM_vector<1, T> operator-(const FM_vector<1, T> &u)
  {
    return FM_vector<1, T>(-u.d[0]);
  }
  friend FM_vector<1, T> operator+(const FM_vector<1, T> &lhs,
                                   const FM_vector<1, T> &rhs)
  {
    return FM_vector<1, T>(lhs.d[0] + rhs.d[0]);
  }
  friend FM_vector<1, T> operator-(const FM_vector<1, T> &lhs,
                                   const FM_vector<1, T> &rhs)
  {
    return FM_vector<1, T>(lhs.d[0] - rhs.d[0]);
  }
  friend FM_vector<1, T>
  operator*(typename FM_traits<T>::element_type lhs,
            const FM_vector<1, T> &rhs)
  {
    return FM_vector<1, T>(lhs * rhs.d[0]);
  }
  friend FM_vector<1, T>
  operator*(const FM_vector<1, T> &lhs,
            typename FM_traits<T>::element_type rhs)
  {
    return FM_vector<1, T>(lhs.d[0] * rhs);
  }
  friend T FM_dot<T>(const FM_vector<1, T> &,
                     const FM_vector<1, T> &);

private:
  T d[1];
};
template <typename T>
class FM_vector<2, T>
{
public:
  FM_vector() {}
  FM_vector(const T dat[])
  {
    d[0] = dat[0];
    d[1] = dat[1];
  }
  template <typename S>
  explicit FM_vector(const FM_vector<2, S> &dat)
  {
    d[0] = (T)dat[0];
    d[1] = (T)dat[1];
  }
  FM_vector(const T &a0, const T &a1)
  {
    d[0] = a0;
    d[1] = a1;
  }
  T &operator[](int i) { return d[i]; }
  const T &operator[](int i) const { return d[i]; }
  operator const T *() const
  {
    return (typename FM_traits<T>::element_type *)d;
  }
  15 friend bool operator==(const FM_vector<2, T> &lhs,
                            const FM_vector<2, T> &rhs)
  {
    return lhs.d[0] == rhs.d[0] &&
           lhs.d[1] == rhs.d[1];
  }
  FM_vector<2, T> &operator+=(const FM_vector<2, T> &v)
  {
    d[0] += v[0];
    d[1] += v[1];
    return *this;
  }
  FM_vector<2, T> &operator-=(const FM_vector<2, T> &v)
  {
    d[0] -= v[0];
    d[1] -= v[1];
    return *this;
  }
  FM_vector<2, T> &operator*=(typename FM_traits<T>::element_type s)
  {
    d[0] *= s;
    d[1] *= s;
    return *this;
  }
  FM_vector<2, T> &operator/=(typename FM_traits<T>::element_type s)
  {
    d[0] /= s;
    d[1] /= s;
    return *this;
  }
  friend FM_vector<2, T> operator-(const FM_vector<2, T> &u)
  {
    return FM_vector<2, T>(-u.d[0], -u.d[1]);
  }
  friend FM_vector<2, T> operator+(const FM_vector<2, T> &lhs,
                                   const FM_vector<2, T> &rhs)
  {
    return FM_vector<2, T>(lhs.d[0] + rhs.d[0],
                           lhs.d[1] + rhs.d[1]);
  }
  friend FM_vector<2, T> operator-(const FM_vector<2, T> &lhs,
                                   const FM_vector<2, T> &rhs)
  {
    return FM_vector<2, T>(lhs.d[0] - rhs.d[0],
                           lhs.d[1] - rhs.d[1]);
  }
  friend FM_vector<2, T>
  operator*(typename FM_traits<T>::element_type lhs,
            const FM_vector<2, T> &rhs)
  {
    return FM_vector<2, T>(lhs * rhs.d[0],
                           lhs * rhs.d[1]);
  }
  friend FM_vector<2, T>
  operator*(const FM_vector<2, T> &lhs,
            typename FM_traits<T>::element_type rhs)
  {
    return FM_vector<2, T>(lhs.d[0] * rhs,
                           lhs.d[1] * rhs);
  }
  friend T FM_dot<T>(const FM_vector<2, T> &,
                     const FM_vector<2, T> &);
  16 private : T d[2];
};
template <typename T>
class FM_vector<3, T>
{
public:
  FM_vector() {}
  FM_vector(const T dat[])
  {
    d[0] = dat[0];
    d[1] = dat[1];
    d[2] = dat[2];
  }
  template <typename S>
  explicit FM_vector(const FM_vector<3, S> &dat)
  {
    d[0] = (T)dat[0];
    d[1] = (T)dat[1];
    d[2] = (T)dat[2];
  }
  FM_vector(const T &a0, const T &a1, const T &a2)
  {
    d[0] = a0;
    d[1] = a1;
    d[2] = a2;
  }
  T &operator[](int i) { return d[i]; }
  const T &operator[](int i) const { return d[i]; }
  operator const T *() const
  {
    return (typename FM_traits<T>::element_type *)d;
  }
  friend bool operator==(const FM_vector<3, T> &lhs,
                         const FM_vector<3, T> &rhs)
  {
    return lhs.d[0] == rhs.d[0] &&
           lhs.d[1] == rhs.d[1] &&
           lhs.d[2] == rhs.d[2];
  }
  FM_vector<3, T> &operator+=(const FM_vector<3, T> &v)
  {
    d[0] += v[0];
    d[1] += v[1];
    d[2] += v[2];
    return *this;
  }
  FM_vector<3, T> &operator-=(const FM_vector<3, T> &v)
  {
    d[0] -= v[0];
    d[1] -= v[1];
    d[2] -= v[2];
    return *this;
  }
  FM_vector<3, T> &operator*=(typename FM_traits<T>::element_type s)
  {
    d[0] *= s;
    d[1] *= s;
    d[2] *= s;
    return *this;
  }
  17 FM_vector<3, T> &operator/=(typename FM_traits<T>::element_type s)
  {
    d[0] /= s;
    d[1] /= s;
    d[2] /= s;
    return *this;
  }
  friend FM_vector<3, T> operator-(const FM_vector<3, T> &u)
  {
    return FM_vector<3, T>(-u.d[0], -u.d[1], -u.d[2]);
  }
  friend FM_vector<3, T> operator+(const FM_vector<3, T> &lhs,
                                   const FM_vector<3, T> &rhs)
  {
    return FM_vector<3, T>(lhs.d[0] + rhs.d[0],
                           lhs.d[1] + rhs.d[1],
                           lhs.d[2] + rhs.d[2]);
  }
  friend FM_vector<3, T> operator-(const FM_vector<3, T> &lhs,
                                   const FM_vector<3, T> &rhs)
  {
    return FM_vector<3, T>(lhs.d[0] - rhs.d[0],
                           lhs.d[1] - rhs.d[1],
                           lhs.d[2] - rhs.d[2]);
  }
  friend FM_vector<3, T>
  operator*(typename FM_traits<T>::element_type lhs,
            const FM_vector<3, T> &rhs)
  {
    return FM_vector<3, T>(lhs * rhs.d[0],
                           lhs * rhs.d[1],
                           lhs * rhs.d[2]);
  }
  friend FM_vector<3, T>
  operator*(const FM_vector<3, T> &lhs,
            typename FM_traits<T>::element_type rhs)
  {
    return FM_vector<3, T>(lhs.d[0] * rhs,
                           lhs.d[1] * rhs,
                           lhs.d[2] * rhs);
  }
  friend T FM_dot<T>(const FM_vector<3, T> &,
                     const FM_vector<3, T> &);
  friend FM_vector<3, T> FM_cross<T>(const FM_vector<3, T> &,
                                     const FM_vector<3, T> &);

private:
  T d[3];
};
template <typename T>
class FM_vector<4, T>
{
public:
  FM_vector() {}
  FM_vector(const T dat[])
  {
    d[0] = dat[0];
    d[1] = dat[1];
    d[2] = dat[2];
    d[3] = dat[3];
  }
  template <typename S >
            18 explicit FM_vector(const FM_vector<3, S> &dat)
  {
    d[0] = (T)dat[0];
    d[1] = (T)dat[1];
    d[2] = (T)dat[2];
    d[3] = (T)dat[3];
  }
  FM_vector(const T &a0, const T &a1, const T &a2, const T &a3)
  {
    d[0] = a0;
    d[1] = a1;
    d[2] = a2;
    d[3] = a3;
  }
  T &operator[](int i) { return d[i]; }
  const T &operator[](int i) const { return d[i]; }
  operator const T *() const
  {
    return (typename FM_traits<T>::element_type *)d;
  }
  friend bool operator==(const FM_vector<4, T> &lhs,
                         const FM_vector<4, T> &rhs)
  {
    return lhs.d[0] == rhs.d[0] &&
           lhs.d[1] == rhs.d[1] &&
           lhs.d[2] == rhs.d[2] &&
           lhs.d[3] == rhs.d[3];
  }
  FM_vector<4, T> &operator+=(const FM_vector<4, T> &v)
  {
    d[0] += v[0];
    d[1] += v[1];
    d[2] += v[2];
    d[3] += v[3];
    return *this;
  }
  FM_vector<4, T> &operator-=(const FM_vector<4, T> &v)
  {
    d[0] -= v[0];
    d[1] -= v[1];
    d[2] -= v[2];
    d[3] -= v[3];
    return *this;
  }
  FM_vector<4, T> &operator*=(typename FM_traits<T>::element_type s)
  {
    d[0] *= s;
    d[1] *= s;
    d[2] *= s;
    d[3] *= s;
    return *this;
  }
  FM_vector<4, T> &operator/=(typename FM_traits<T>::element_type s)
  {
    d[0] /= s;
    d[1] /= s;
    d[2] /= s;
    d[3] /= s;
    return *this;
  }
  friend FM_vector<4, T> operator-(const FM_vector<4, T> &u)
  {
    return FM_vector<4, T>(-u.d[0], -u.d[1], -u.d[2], -u.d[3]);
    19
  }
  friend FM_vector<4, T> operator+(const FM_vector<4, T> &lhs,
                                   const FM_vector<4, T> &rhs)
  {
    return FM_vector<4, T>(lhs.d[0] + rhs.d[0],
                           lhs.d[1] + rhs.d[1],
                           lhs.d[2] + rhs.d[2],
                           lhs.d[3] + rhs.d[3]);
  }
  friend FM_vector<4, T> operator-(const FM_vector<4, T> &lhs,
                                   const FM_vector<4, T> &rhs)
  {
    return FM_vector<4, T>(lhs.d[0] - rhs.d[0],
                           lhs.d[1] - rhs.d[1],
                           lhs.d[2] - rhs.d[2],
                           lhs.d[3] - rhs.d[3]);
  }
  friend FM_vector<4, T>
  operator*(typename FM_traits<T>::element_type lhs,
            const FM_vector<4, T> &rhs)
  {
    return FM_vector<4, T>(lhs * rhs.d[0],
                           lhs * rhs.d[1],
                           lhs * rhs.d[2],
                           lhs * rhs.d[3]);
  }
  friend FM_vector<4, T>
  operator*(const FM_vector<4, T> &lhs,
            typename FM_traits<T>::element_type rhs)
  {
    return FM_vector<4, T>(lhs.d[0] * rhs,
                           lhs.d[1] * rhs,
                           lhs.d[2] * rhs,
                           lhs.d[3] * rhs);
  }
  friend T FM_dot<T>(const FM_vector<4, T> &,
                     const FM_vector<4, T> &);

private:
  T d[4];
};
template <int N, typename T>
bool operator!=(const FM_vector<N, T> &lhs,
                const FM_vector<N, T> &rhs)
{
  return !(lhs == rhs);
}
template <int N, typename T>
std::ostream &operator<<(std::ostream &lhs,
                         const FM_vector<N, T> &rhs)
{
  lhs << "(";
  lhs << rhs[0];
  for (int i = 1; i < N; i++)
    lhs << ", " << rhs[i];
  return lhs << ")";
}
template <int N, typename T>
T FM_dot(const FM_vector<N, T> &lhs, const FM_vector<N, T> &rhs)
{
  T res = lhs[0] * rhs[0];
  for (int i = 1; i < N; i++)
    res += lhs[i] * rhs[i];
  return res;
}
template <typename T>
T FM_dot(const FM_vector<1, T> &lhs,
         const FM_vector<1, T> &rhs)
{
  return lhs.d[0] * rhs.d[0];
}
template <typename T>
T FM_dot(const FM_vector<2, T> &lhs,
         const FM_vector<2, T> &rhs)
{
  return lhs.d[0] * rhs.d[0] +
         lhs.d[1] * rhs.d[1];
}
template <typename T>
T FM_dot(const FM_vector<3, T> &lhs,
         const FM_vector<3, T> &rhs)
{
  return lhs.d[0] * rhs.d[0] +
         lhs.d[1] * rhs.d[1] +
         lhs.d[2] * rhs.d[2];
}
template <typename T>
T FM_dot(const FM_vector<4, T> &lhs,
         const FM_vector<4, T> &rhs)
{
  return lhs.d[0] * rhs.d[0] +
         lhs.d[1] * rhs.d[1] +
         lhs.d[2] * rhs.d[2] +
         lhs.d[3] * rhs.d[3];
}
template <typename T>
FM_vector<3, T> FM_cross(const FM_vector<3, T> &lhs,
                         const FM_vector<3, T> &rhs)
{
  return FM_vector<3, T>(lhs.d[1] * rhs.d[2] - rhs.d[1] * lhs.d[2],
                         rhs.d[0] * lhs.d[2] - lhs.d[0] * rhs.d[2],
                         lhs.d[0] * rhs.d[1] - rhs.d[0] * lhs.d[1]);
}
template <int N, typename T>
T FM_mag(const FM_vector<N, T> &v)
{
  return (T)sqrt(FM_dot(v, v));
}
template <int N, typename T>
T FM_distance2(const FM_vector<N, T> &lhs, const FM_vector<N, T> &rhs)
{
  FM_vector<N, T> d = rhs - lhs;
  21 return FM_dot(d, d);
}
template <int N>
FM_vector<N, bool> operator!(const FM_vector<N, bool> &u)
{
  bool tmp[N];
  for (int i = 0; i < N; i++)
    tmp[i] = !u[i];
  return FM_vector<N, bool>(tmp);
}
template <int N>
FM_vector<N, bool> operator&&(const FM_vector<N, bool> &lhs,
                              const FM_vector<N, bool> &rhs)
{
  bool tmp[N];
  for (int i = 0; i < N; i++)
    tmp[i] = lhs[i] && rhs[i];
  return FM_vector<N, bool>(tmp);
}
template <int N>
FM_vector<N, bool> operator||(const FM_vector<N, bool> &lhs,
                              const FM_vector<N, bool> &rhs)
{
  bool tmp[N];
  for (int i = 0; i < N; i++)
    tmp[i] = lhs[i] || rhs[i];
  return FM_vector<N, bool>(tmp);
}
template <int N>
FM_vector<N, bool> operatorˆ(const FM_vector<N, bool> &lhs,
                             const FM_vector<N, bool> &rhs)
{
  bool tmp[N];
  for (int i = 0; i < N; i++)
    tmp[i] = lhs[i] ˆ rhs[i];
  return FM_vector<N, bool>(tmp);
}
template <int N>
bool operator<=(const FM_vector<N, bool> &lhs,
                const FM_vector<N, bool> &rhs)
{
  bool res = true;
  for (int i = 0; i < N; i++)
  {
    if (lhs[i] && !rhs[i])
    {
      res = false;
      break;
    }
  }
  return res;
}
template <int N>
bool operator>=(const FM_vector<N, bool> &lhs,
                const FM_vector<N, bool> &rhs)
{
  bool res = true;
  for (int i = 0; i < N; i++)
  {
    if (!lhs[i] && rhs[i])
    {
      res = false;
      break;
    }
  }
  22 return res;
}
typedef FM_vector<2, int> FM_vector2i;
typedef FM_vector<2, float> FM_vector2f;
typedef FM_vector<2, double> FM_vector2d;
typedef FM_vector<3, int> FM_vector3i;
typedef FM_vector<3, float> FM_vector3f;
typedef FM_vector<3, double> FM_vector3d;
typedef FM_vector<4, int> FM_vector4i;
typedef FM_vector<4, float> FM_vector4f;
typedef FM_vector<4, double> FM_vector4d;
/*
 * Copyright (c) 2000
 * Advanced Management Technology, Incorporated
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software
 * and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY
 * OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * LOG:
 * $Log$
 */
#endif
23
// Emacs mode -*-c++-*- //
#ifndef _FM_MATRIX_H_
#define _FM_MATRIX_H_
/*
 * NAME: FM_matrix.h
 *
 * WRITTEN BY:
 * Patrick Moran pmoran@nas.nasa.gov
 */
#include "FM_vector.h"
    template <int M, int N, typename T>
    FM_vector<N, T>
    operator*(const FM_vector<M, T> &lhs,
              const FM_vector<M, FM_vector<N, T>> &rhs)
{
  T tmp[N], sum;
  for (int n = 0; n < N; n++)
  {
    sum = (T)0;
    for (int m = 0; m < M; m++)
    {
      sum += lhs[m] * rhs[m][n];
    }
    tmp[n] = sum;
  }
  return FM_vector<N, T>(tmp);
}
template <typename T>
FM_vector<3, T>
operator*(const FM_vector<3, T> &lhs,
          const FM_vector<3, FM_vector<3, T>> &rhs)
{
  return FM_vector<3, T>(lhs[0] * rhs[0][0] +
                             lhs[1] * rhs[1][0] +
                             lhs[2] * rhs[2][0],
                         lhs[0] * rhs[0][1] +
                             lhs[1] * rhs[1][1] +
                             lhs[2] * rhs[2][1],
                         lhs[0] * rhs[0][2] +
                             lhs[1] * rhs[1][2] +
                             lhs[2] * rhs[2][2]);
}
template <typename T>
FM_vector<4, T>
operator*(const FM_vector<4, T> &lhs,
          const FM_vector<4, FM_vector<4, T>> &rhs)
{
  return FM_vector<4, T>(lhs[0] * rhs[0][0] +
                             lhs[1] * rhs[1][0] +
                             lhs[2] * rhs[2][0] +
                             lhs[3] * rhs[3][0],
                         lhs[0] * rhs[0][1] +
                             lhs[1] * rhs[1][1] +
                             lhs[2] * rhs[2][1] +
                             lhs[3] * rhs[3][1],
                         lhs[0] * rhs[0][2] +
                             lhs[1] * rhs[1][2] +
                             lhs[2] * rhs[2][2] +
                             lhs[3] * rhs[3][2],
                         lhs[0] * rhs[0][3] +
                             lhs[1] * rhs[1][3] +
                             lhs[2] * rhs[2][3] +
                             lhs[3] * rhs[3][3]);
}
24 template <int M, int N, typename T>
FM_vector<M, T>
operator*(const FM_vector<M, FM_vector<N, T>> &lhs,
          const FM_vector<N, T> &rhs)
{
  T tmp[M];
  for (int m = 0; m < M; m++)
  {
    tmp[m] = FM_dot(lhs[m], rhs);
  }
  return FM_vector<M, T>(tmp);
}
template <typename T>
FM_vector<3, T>
operator*(const FM_vector<3, FM_vector<3, T>> &lhs,
          const FM_vector<3, T> &rhs)
{
  return FM_vector<3, T>(FM_dot(lhs[0], rhs),
                         FM_dot(lhs[1], rhs),
                         FM_dot(lhs[2], rhs));
}
template <typename T>
FM_vector<4, T>
operator*(const FM_vector<4, FM_vector<4, T>> &lhs,
          const FM_vector<4, T> &rhs)
{
  return FM_vector<4, T>(FM_dot(lhs[0], rhs),
                         FM_dot(lhs[1], rhs),
                         FM_dot(lhs[2], rhs),
                         FM_dot(lhs[3], rhs));
}
template <int M, int N, int P, typename T>
FM_vector<M, FM_vector<P, T>>
operator*(const FM_vector<M, FM_vector<N, T>> &lhs,
          const FM_vector<N, FM_vector<P, T>> &rhs)
{
  FM_vector<P, T> tmp[M];
  T sum;
  for (int m = 0; m < M; m++)
  {
    for (int p = 0; p < P; p++)
    {
      sum = (T)0;
      for (int n = 0; n < N; n++)
      {
        sum += lhs[m][n] * rhs[n][p];
      }
      tmp[m][p] = sum;
    }
  }
  return FM_vector<M, FM_vector<P, T>>(tmp);
}
template <int M, int N, typename T>
FM_vector<N, FM_vector<M, T>>
FM_transpose(const FM_vector<M, FM_vector<N, T>> &in)
{
  FM_vector<M, T> tmp[N];
  for (int m = 0; m < M; m++)
  {
    for (int n = 0; n < N; n++)
    {
      tmp[n][m] = in[m][n];
    }
  }
  return FM_vector<N, FM_vector<M, T>>(tmp);
}
template <typename T >
          25 FM_vector<3, FM_vector<3, T>>
          FM_transpose(const FM_vector<3, FM_vector<3, T>> &in)
{
  return FM_vector<3, FM_vector<3, T>>(FM_vector<3, T>(in[0][0], in[1][0], in[2][0]),
                                       FM_vector<3, T>(in[0][1], in[1][1], in[2][1]),
                                       FM_vector<3, T>(in[0][2], in[1][2], in[2][2]));
}
template <int N, typename T>
T FM_det(const FM_vector<N, FM_vector<N, T>> &);
template <int N, typename T>
T FM_minor(const FM_vector<N, FM_vector<N, T>> &in, int row, int col)
{
  FM_vector<N - 1, FM_vector<N - 1, T>> tmp;
  int dst_row, dst_col;
  dst_row = 0;
  for (int src_row = 0; src_row < N; src_row++)
  {
    if (src_row == row)
      continue;
    dst_col = 0;
    for (int src_col = 0; src_col < N; src_col++)
    {
      if (src_col == col)
        continue;
      tmp[dst_row][dst_col] = in[src_row][src_col];
      dst_col++;
    }
    dst_row++;
  }
  return FM_det(tmp);
}
template <int N, typename T>
T FM_det(const FM_vector<N, FM_vector<N, T>> &in)
{
  T sum = (T)0;
  for (int n = 0; n < N; n++)
  {
    T minor = FM_minor(in, n, 0);
    T cofactor = (n & 1) ? -minor : minor;
    sum += in[n][0] * cofactor;
  }
  return sum;
}
template <typename T>
T FM_det(const FM_vector<1, FM_vector<1, T>> &in)
{
  return in[0][0];
}
template <typename T>
T FM_det(const FM_vector<2, FM_vector<2, T>> &in)
{
  return in[0][0] * in[1][1] - in[1][0] * in[0][1];
}
template <typename T>
T FM_det(const FM_vector<3, FM_vector<3, T>> &in)
{
  return in[0][0] * (in[1][1] * in[2][2] - in[2][1] * in[1][2]) -
         in[1][0] * (in[0][1] * in[2][2] - in[2][1] * in[0][2]) +
         in[2][0] * (in[0][1] * in[1][2] - in[1][1] * in[0][2]);
}
template <typename T>
T FM_det(const FM_vector<4, FM_vector<4, T>> &in)
{
  26
      // columns 2,3
      T r0r1 = in[0][2] * in[1][3] - in[1][2] * in[0][3];
  T r0r2 = in[0][2] * in[2][3] - in[2][2] * in[0][3];
  T r0r3 = in[0][2] * in[3][3] - in[3][2] * in[0][3];
  T r1r2 = in[1][2] * in[2][3] - in[2][2] * in[1][3];
  T r1r3 = in[1][2] * in[3][3] - in[3][2] * in[1][3];
  T r2r3 = in[2][2] * in[3][3] - in[3][2] * in[2][3];
  // column 0
  T minor0 = in[1][1] * r2r3 - in[2][1] * r1r3 + in[3][1] * r1r2;
  T minor1 = in[0][1] * r2r3 - in[2][1] * r0r3 + in[3][1] * r0r2;
  T minor2 = in[0][1] * r1r3 - in[1][1] * r0r3 + in[3][1] * r0r1;
  T minor3 = in[0][1] * r1r2 - in[1][1] * r0r2 + in[2][1] * r0r1;
  return in[0][0] * minor0 -
         in[1][0] * minor1 +
         in[2][0] * minor2 -
         in[3][0] * minor3;
}
template <int N, typename T>
FM_vector<N, FM_vector<N, T>>
FM_adj(const FM_vector<N, FM_vector<N, T>> &in)
{
  FM_vector<N, FM_vector<N, T>> res;
  for (int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
    {
      T minor = FM_minor(in, row, col);
      T cofactor = ((row + col) & 1) ? -minor : minor;
      res[col][row] = cofactor; // transpose
    }
  }
  return res;
}
template <int N, typename T>
int FM_inv(const FM_vector<N, FM_vector<N, T>> &in,
           FM_vector<N, FM_vector<N, T>> *out)
{
  T det = FM_det(in);
  if (det == (T)0)
    return 1;
  *out = (T)1 / det * FM_adj(in);
  return 0;
}
template <typename T>
int FM_inv(const FM_vector<2, FM_vector<2, T>> &in,
           FM_vector<2, FM_vector<2, T>> *out)
{
  T det = FM_det(in);
  if (det == (T)0)
    return 1;
  T inv_det = (T)1 / det;
  (*out)[0][0] = inv_det * in[1][1];
  (*out)[0][1] = inv_det * -in[0][1];
  (*out)[1][0] = inv_det * -in[1][0];
  (*out)[1][1] = inv_det * in[0][0];
  return 0;
}
template <typename T>
int FM_inv(const FM_vector<3, FM_vector<3, T>> &in,
           FM_vector<3, FM_vector<3, T>> *out)
{
  27
      // column 0
      T minor0 = in[1][1] * in[2][2] - in[2][1] * in[1][2];
  T minor1 = in[0][1] * in[2][2] - in[2][1] * in[0][2];
  T minor2 = in[0][1] * in[1][2] - in[1][1] * in[0][2];
  T det =
      in[0][0] * minor0 -
      in[1][0] * minor1 +
      in[2][0] * minor2;
  if (det == (T)0)
    return 1;
  T inv_det = (T)1 / det;
  (*out)[0][0] = inv_det * minor0;
  (*out)[0][1] = inv_det * -minor1;
  (*out)[0][2] = inv_det * minor2;
  (*out)[1][0] = inv_det * (in[2][0] * in[1][2] - in[1][0] * in[2][2]);
  (*out)[1][1] = inv_det * (in[0][0] * in[2][2] - in[2][0] * in[0][2]);
  (*out)[1][2] = inv_det * (in[1][0] * in[0][2] - in[0][0] * in[1][2]);
  (*out)[2][0] = inv_det * (in[1][0] * in[2][1] - in[2][0] * in[1][1]);
  (*out)[2][1] = inv_det * (in[2][0] * in[0][1] - in[0][0] * in[2][1]);
  (*out)[2][2] = inv_det * (in[0][0] * in[1][1] - in[1][0] * in[0][1]);
  return 0;
}
template <typename T>
int FM_inv(const FM_vector<4, FM_vector<4, T>> &in,
           FM_vector<4, FM_vector<4, T>> *out)
{
  // compute minors column by column, but fill in (*out) row
  // by row to effectively transpose
  // columns 2,3
  T r0r1 = in[0][2] * in[1][3] - in[1][2] * in[0][3];
  T r0r2 = in[0][2] * in[2][3] - in[2][2] * in[0][3];
  T r0r3 = in[0][2] * in[3][3] - in[3][2] * in[0][3];
  T r1r2 = in[1][2] * in[2][3] - in[2][2] * in[1][3];
  T r1r3 = in[1][2] * in[3][3] - in[3][2] * in[1][3];
  T r2r3 = in[2][2] * in[3][3] - in[3][2] * in[2][3];
  // column 0
  T minor0 = in[1][1] * r2r3 - in[2][1] * r1r3 + in[3][1] * r1r2;
  T minor1 = in[0][1] * r2r3 - in[2][1] * r0r3 + in[3][1] * r0r2;
  T minor2 = in[0][1] * r1r3 - in[1][1] * r0r3 + in[3][1] * r0r1;
  T minor3 = in[0][1] * r1r2 - in[1][1] * r0r2 + in[2][1] * r0r1;
  T det =
      in[0][0] * minor0 -
      in[1][0] * minor1 +
      in[2][0] * minor2 -
      in[3][0] * minor3;
  if (det == (T)0)
    return 1;
  T inv_det = (T)1 / det;
  (*out)[0][0] = inv_det * minor0;
  (*out)[0][1] = inv_det * -minor1;
  (*out)[0][2] = inv_det * minor2;
  (*out)[0][3] = inv_det * -minor3;
  // column 1
  minor0 = in[1][0] * r2r3 - in[2][0] * r1r3 + in[3][0] * r1r2;
  minor1 = in[0][0] * r2r3 - in[2][0] * r0r3 + in[3][0] * r0r2;
  minor2 = in[0][0] * r1r3 - in[1][0] * r0r3 + in[3][0] * r0r1;
  28 minor3 = in[0][0] * r1r2 - in[1][0] * r0r2 + in[2][0] * r0r1;
  (*out)[1][0] = inv_det * -minor0;
  (*out)[1][1] = inv_det * minor1;
  (*out)[1][2] = inv_det * -minor2;
  (*out)[1][3] = inv_det * minor3;
  // columns 0,1
  r0r1 = in[0][0] * in[1][1] - in[1][0] * in[0][1];
  r0r2 = in[0][0] * in[2][1] - in[2][0] * in[0][1];
  r0r3 = in[0][0] * in[3][1] - in[3][0] * in[0][1];
  r1r2 = in[1][0] * in[2][1] - in[2][0] * in[1][1];
  r1r3 = in[1][0] * in[3][1] - in[3][0] * in[1][1];
  r2r3 = in[2][0] * in[3][1] - in[3][0] * in[2][1];
  // column 2
  minor0 = in[1][3] * r2r3 - in[2][3] * r1r3 + in[3][3] * r1r2;
  minor1 = in[0][3] * r2r3 - in[2][3] * r0r3 + in[3][3] * r0r2;
  minor2 = in[0][3] * r1r3 - in[1][3] * r0r3 + in[3][3] * r0r1;
  minor3 = in[0][3] * r1r2 - in[1][3] * r0r2 + in[2][3] * r0r1;
  (*out)[2][0] = inv_det * minor0;
  (*out)[2][1] = inv_det * -minor1;
  (*out)[2][2] = inv_det * minor2;
  (*out)[2][3] = inv_det * -minor3;
  // column 3
  minor0 = in[1][2] * r2r3 - in[2][2] * r1r3 + in[3][2] * r1r2;
  minor1 = in[0][2] * r2r3 - in[2][2] * r0r3 + in[3][2] * r0r2;
  minor2 = in[0][2] * r1r3 - in[1][2] * r0r3 + in[3][2] * r0r1;
  minor3 = in[0][2] * r1r2 - in[1][2] * r0r2 + in[2][2] * r0r1;
  (*out)[3][0] = inv_det * -minor0;
  (*out)[3][1] = inv_det * minor1;
  (*out)[3][2] = inv_det * -minor2;
  (*out)[3][3] = inv_det * minor3;
  return 0;
}
template <int N, typename T>
void FM_identity(FM_vector<N, FM_vector<N, T>> *out)
{
  T zero = (T)0;
  T one = (T)1;
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      (*out)[row][col] = row == col ? one : zero;
}
typedef FM_vector<2, FM_vector<2, float>> FM_matrix22f;
typedef FM_vector<2, FM_vector<3, float>> FM_matrix23f;
typedef FM_vector<3, FM_vector<2, float>> FM_matrix32f;
typedef FM_vector<3, FM_vector<3, float>> FM_matrix33f;
typedef FM_vector<3, FM_vector<3, double>> FM_matrix33d;
typedef FM_vector<4, FM_vector<4, float>> FM_matrix44f;
typedef FM_vector<4, FM_vector<4, double>> FM_matrix44d;
/*
* Copyright (c) 2000
* Advanced Management Technology, Incorporated
*
* Permission is hereby granted, free of charge,
* to any person obtaining a copy of this software
* and associated documentation files (the "Software"),
29
* to deal in the Software without restriction,
* including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission
* notice shall be included in all copies or substantial
* portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY
* OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
* EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
* THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* LOG:
* $Log$
*/
#endif
30
// Emacs mode -*-c++-*- //
#ifndef _FM_TIMER_H_
#define _FM_TIMER_H_
/*
 * NAME: FM_timer.h
 *
 * WRITTEN BY:
 * Patrick Moran pmoran@nas.nasa.gov
 */
#include <sys/time.h>
    class FM_timer
{
public:
  FM_timer() { reset(); }
  void reset() { total = 0.0; }
  void start() { gettimeofday(&start_tv, (struct timezone *)0); }
  void stop()
  {
    struct timeval stop_tv;
    gettimeofday(&stop_tv, (struct timezone *)0);
    long dts = stop_tv.tv_sec - start_tv.tv_sec;
    long dtus = stop_tv.tv_usec - start_tv.tv_usec;
    double dt = (double)dts + (double)dtus * 1.0e-6;
    // round to milliseconds
    long millisec = (long)(dt * 1000.0 + 0.5);
    total += millisec * 1000.0;
  }
  double elapsed() { return total; }

private:
  struct timeval start_tv;
  double total;
};
/*
 * Copyright (c) 2000
 * Advanced Management Technology, Incorporated
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software
 * and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission
 * notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY
 * OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * LOG:
 * $Log$
 */
#endif
31
/*
 * NAME: vector_tests
 *
 * WRITTEN BY:
 * Patrick Moran pmoran@nas.nasa.gov
 */
#include <assert.h>
#include <stdlib.h>
#include "FM_vector.h"
#include "FM_matrix.h"
#include "FM_timer.h"
    void
    random_init(int *i)
{
  *i = rand() % 10 - 5;
}
void random_init(float *f)
{
  *f = (float)(rand() % 20 - 10);
}
void random_init(double *d)
{
  *d = (double)(rand() % 20 - 10);
}
template <int N, typename T>
void random_init(FM_vector<N, T> *v)
{
  for (int i = 0; i < N; i++)
    random_init(&((*v)[i]));
}
template <typename T>
T max_mag(T t)
{
  return t >= (T)0 ? t : -t;
}
template <int N, typename T>
typename FM_traits<T>::element_type
max_mag(const FM_vector<N, T> &v)
{
  typename FM_traits<T>::element_type res =
      (typename FM_traits<T>::element_type)0;
  for (int i = 0; i < N; i++)
  {
    typename FM_traits<T>::element_type e = max_mag(v[i]);
    if (e > res)
      res = e;
  }
  return res;
}
inline static double fmax(double a, double b)
{
  return a > b ? a : b;
}
template <int N, typename T>
void general_tests()
{
  int i;
  T a[N];
  for (i = 0; i < N; i++)
    32 random_init(&a[i]);
  // FM_vector(const T[])
  // T& operator[](int)
  FM_vector<N, T> u(a);
  for (i = 0; i < N; i++)
    assert(u[i] == a[i]);
  for (i = 0; i < N; i++)
    u[i] = u[i];
  for (i = 0; i < N; i++)
    assert(u[i] == a[i]);
  // const T& operator[](int) const
  const FM_vector<N, T> cu = u;
  for (i = 0; i < N; i++)
    assert(u[i] == cu[i]);
  // FM_vector(T, T, ...)
  // friend bool operator==(const FM_vector<N,T>&,
  //  const FM_vector<N,T>&)
  // friend bool operator!=(const FM_vector<N,T>&,
  //  const FM_vector<N,T>&)
  assert(u == u);
  assert(!(u != u));
  FM_vector<N, T> v = u;
  while (u == v)
    random_init(&v);
  assert(u != v);
  // friend FM_vector<N,T> operator+(const FM_vector<N,T>&,
  //  const FM_vector<N,T>&)
  FM_vector<N, T> w = u + v;
  for (i = 0; i < N; i++)
    assert(w[i] == u[i] + v[i]);
  // friend ostream& operator<<(ostream&,
  //  const FM_vector<N,T>&)
  // std::cout << v << endl;
  // FM_vector<N,T> operator*(typename FM_traits<T>::element_type,
  //  const FM_vector<N,T>&)
  typename FM_traits<T>::element_type s = 0;
  random_init(&s);
  v = s * u;
  for (i = 0; i < N; i++)
    assert(v[i] == s * u[i]);
  // FM_vector<N,T> operator*(const FM_vector<N,T>&,
  //  typename FM_traits<T>::element_type)
  v = u * s;
  for (i = 0; i < N; i++)
    assert(v[i] == u[i] * s);
  random_init(&u);
  random_init(&v);
  // friend FM_vector<N,T> operator-(const FM_vector<N,T>&)
  w = -u;
  for (i = 0; i < N; i++)
    assert(w[i] == -u[i]);
  // friend FM_vector<N,T> operator-(const FM_vector<N,T>&,
  //  const FM_vector<N,T>&)
  w = u - v;
  for (i = 0; i < N; i++)
    assert(w[i] == u[i] - v[i]);
}
33 template <int N, typename T>
void vector_of_scalars_tests()
{
  int i;
  int sum;
  FM_vector<N, T> u, v;
  random_init(&u);
  random_init(&v);
  // friend T FM_dot(const FM_vector<N,T>&,
  //  const FM_vector<N,T>&)
  sum = 0;
  for (i = 0; i < N; i++)
    sum += u[i] * v[i];
  assert(sum == FM_dot(u, v));
  // friend FM_vector<3,T> FM_cross(const FM_vector<3,T>&,
  //  const FM_vector<3,T>&)
  T t;
  FM_vector<3, T> t3, u3, v3, w3, x3;
  random_init(&u3);
  random_init(&v3);
  random_init(&w3);
  random_init(&x3);
  // u3 x (v3 x w3) == v3(u3 . w3) - w3(u3 . v3)
  t3 = FM_cross(u3, FM_cross(v3, w3)) -
       (v3 * FM_dot(u3, w3) - w3 * FM_dot(u3, v3));
  assert(max_mag(t3) == 0);
  // (u3 x v3) x w3 == v3(u3 . w3) - u3(v3 . w3)
  t3 = FM_cross(FM_cross(u3, v3), w3) -
       (v3 * FM_dot(u3, w3) - u3 * FM_dot(v3, w3));
  assert(max_mag(t3) == 0);
  // (u3 x v3) . (w3 x x3) == (u3 . w3)(v3 . x3) - (u3 . x3)(v3 . w3)
  t = FM_dot(FM_cross(u3, v3), FM_cross(w3, x3)) -
      (FM_dot(u3, w3) * FM_dot(v3, x3) - FM_dot(u3, x3) * FM_dot(v3, w3));
  assert(t == 0);
  // u3 x (v3 x w3) + v3 x (w3 x u3) + w3 x (u3 x v3) == 0
  t3 = FM_cross(u3, FM_cross(v3, w3)) +
       FM_cross(v3, FM_cross(w3, u3)) + FM_cross(w3, FM_cross(u3, v3));
  assert(max_mag(t3) == 0);
}
template <int N, typename T>
void real_vector_of_scalars_tests()
{
  int i;
  double epsilon = 1e-5;
  FM_vector<N, T> u;
  // friend T FM_mag(const FM_vector<N,T>&)
  random_init(&u);
  double dsum = 0.0;
  for (i = 0; i < N; i++)
    dsum += (double)(u[i] * u[i]);
  assert(fabs(sqrt(dsum) - (double)FM_mag(u)) < epsilon);
}
template <int M, int N, typename T>
void vector_matrix_tests()
{
  34 FM_vector<M, T> uM, vM;
  FM_vector<N, T> uN, vN;
  FM_vector<M, FM_vector<N, T>> mMN;
  FM_vector<N, FM_vector<M, T>> mNM;
  FM_vector<M, FM_vector<M, T>> mMM, miMM, iMM;
  FM_vector<N, FM_vector<N, T>> mNN;
  // Let P = M + N + 3
  FM_vector<M, FM_vector<M + N + 3, T>> mMP;
  FM_vector<N, FM_vector<M + N + 3, T>> mNP;
  FM_vector<M + N + 3, FM_vector<M, T>> mPM;
  int row, col;
  T det;
  // FM_vector<N,FM_vector<M,T> >
  // FM_transpose(const FM_vector<M,FM_vector<N,T> >& in)
  random_init(&mMN);
  mNM = FM_transpose(mMN);
  for (int row = 0; row < M; row++)
    for (int col = 0; col < N; col++)
      assert(mMN[row][col] == mNM[col][row]);
  // FM_vector<N,T>
  // operator*(const FM_vector<M,T>& lhs,
  //  const FM_vector<M,FM_vector<N,T> >& rhs)
  // FM_vector<M,T>
  // operator*(const FM_vector<M,FM_vector<N,T> >& lhs,
  //  const FM_vector<N,T>& rhs)
  random_init(&vM);
  random_init(&mMN);
  uN = vM * mMN - FM_transpose(mMN) * vM;
  assert(max_mag(uN) == (T)0);
  // FM_vector<M,FM_vector<P,T> >
  // operator*(const FM_vector<M,FM_vector<N,T> >& lhs,
  //  const FM_vector<N,FM_vector<P,T> >& rhs)
  random_init(&mMN);
  random_init(&mNP);
  mMP = mMN * mNP;
  mPM = FM_transpose(mNP) * FM_transpose(mMN);
  assert(max_mag(mMP - FM_transpose(mPM)) == (T)0);
  // FM_vector<M,FM_vector<M,T> > FM_identity()
  FM_identity(&mMM);
  for (row = 0; row < M; row++)
    for (col = 0; col < M; col++)
      assert(mMM[row][col] == (row == col ? (T)1 : (T)0));
  // T FM_det(const FM_vector<N,FM_vector<N,T> >&);
  FM_identity(&mMM);
  det = FM_det(mMM);
  assert(det == (T)1);
  const T K = (T)7;
  mMM[0][0] = K;
  det = FM_det(mMM);
  assert(det == K);
  random_init(&mMM);
  assert(FM_det(mMM) - FM_det(FM_transpose(mMM)) == (T)0);
  // FM_vector<N,FM_vector<N,T> >
  // FM_adj(const FM_vector<N,FM_vector<N,T> >& in)
  random_init(&mMM);
  FM_identity(&iMM);
  det = FM_det(mMM);
  assert(max_mag(FM_adj(mMM) * mMM - det * iMM) == 0);
  35
}
template <int M, typename T>
void real_vector_matrix_tests()
{
  int row, res;
  T epsilon = (T)1e-4;
  T det;
  const T K = (T)7;
  FM_vector<M, T> uM, vM;
  FM_vector<M, FM_vector<M, T>> mMM, miMM, iMM;
  // int FM_inv(const FM_vector<N,FM_vector<N,T> >& in,
  //  FM_vector<N,FM_vector<N,T> >* out)
  det = FM_det(mMM);
  while (det == (T)0)
  {
    random_init(&mMM);
    det = FM_det(mMM);
  }
  res = FM_inv(mMM, &miMM);
  assert(res == 0);
  // mMM[0] = K * mMM[M - 1];
  // res = FM_inv(mMM, &miMM);
  // assert(res != 0);
  random_init(&mMM);
  det = FM_det(mMM);
  while (det == (T)0)
  {
    random_init(&mMM);
    det = FM_det(mMM);
  }
  for (row = 0; row < M; row++)
    mMM[row][0] = K * mMM[row][M - 1];
  res = FM_inv(mMM, &miMM);
  assert(res != 0);
  // FM_vector<M,FM_vector<P,T> >
  // operator*(const FM_vector<M,FM_vector<N,T> >& lhs,
  //  const FM_vector<N,FM_vector<P,T> >& rhs)
  FM_identity(&iMM);
  random_init(&mMM);
  res = FM_inv(mMM, &miMM);
  while (res != 0)
  {
    random_init(&mMM);
    res = FM_inv(mMM, &miMM);
  }
  epsilon = 1e-3;
  assert(max_mag(mMM * miMM - iMM) < epsilon);
  assert(max_mag(miMM * mMM - iMM) < epsilon);
  // int FM_inv(const FM_vector<N,FM_vector<N,T> >& in,
  //  FM_vector<N,FM_vector<N,T> >* out)
  det = FM_det(mMM);
  while (det == (T)0)
  {
    random_init(&mMM);
    det = FM_det(mMM);
  }
  res = FM_inv(mMM, &miMM);
  assert(res == 0);
  mMM[0] = K * mMM[M - 1];
  res = FM_inv(mMM, &miMM);
  assert(res != 0);
  random_init(&mMM);
  det = FM_det(mMM);
  while (det == (T)0)
  {
    36 random_init(&mMM);
    det = FM_det(mMM);
  }
  for (row = 0; row < M; row++)
    mMM[row][0] = K * mMM[row][M - 1];
  res = FM_inv(mMM, &miMM);
  assert(res != 0);
  // FM_vector<M,FM_vector<P,T> >
  // operator*(const FM_vector<M,FM_vector<N,T> >& lhs,
  //  const FM_vector<N,FM_vector<P,T> >& rhs)
  FM_identity(&iMM);
  random_init(&mMM);
  res = FM_inv(mMM, &miMM);
  while (res != 0)
  {
    random_init(&mMM);
    res = FM_inv(mMM, &miMM);
  }
  epsilon = 1e-3;
  assert(max_mag(mMM * miMM - iMM) < epsilon);
  assert(max_mag(miMM * mMM - iMM) < epsilon);
}
template <typename T>
inline static int sign(T t)
{
  return t > (T)0 ? 1 : (t < (T)0 ? -1 : 0);
}
template <typename T>
// inline
int orient(const FM_vector<3, T> &a,
           const FM_vector<3, T> &b,
           const FM_vector<3, T> &c,
           const FM_vector<3, T> &d)
{
  return sign(FM_dot(d - a, FM_cross(b - a, c - a)));
}
template <typename T>
void orient_tests(const FM_vector<3, T> &)
{
  int i, res = 0;
  const int N_STMTS = 1;
  const int N_TRIALS = 10000000;
  FM_timer timer;
  double total;
  FM_vector<3, T> a, b, c, d;
  random_init(&a);
  random_init(&b);
  random_init(&c);
  random_init(&d);
  res = 0;
  timer.start();
  for (i = 0; i < N_TRIALS; i++)
  {
    res += orient(a, b, c, d);
  }
  timer.stop();
  res = res;
  total = timer.elapsed();
  std::cout << total / (double)(N_TRIALS * N_STMTS)
            << " usec / orient" << std::endl;
}
37 void timing_tests()
{
  orient_tests(FM_vector<3, float>());
  orient_tests(FM_vector<3, double>());
}
int main()
{
  for (int i = 0; i < 1000; i++)
  {
    general_tests<1, int>();
    general_tests<2, int>();
    general_tests<3, int>();
    general_tests<4, int>();
    general_tests<17, int>();
    general_tests<4, FM_vector<3, int>>();
    general_tests<5, FM_vector<7, int>>();
    general_tests<2, FM_vector<4, FM_vector<3, int>>>();
    general_tests<8, FM_vector<5, FM_vector<7, int>>>();
    vector_of_scalars_tests<2, int>();
    vector_of_scalars_tests<3, int>();
    vector_of_scalars_tests<4, int>();
    vector_of_scalars_tests<5, int>();
    real_vector_of_scalars_tests<2, double>();
    real_vector_of_scalars_tests<3, double>();
    real_vector_of_scalars_tests<4, double>();
    real_vector_of_scalars_tests<5, double>();
    vector_matrix_tests<2, 2, int>();
    vector_matrix_tests<2, 3, int>();
    vector_matrix_tests<2, 4, int>();
    vector_matrix_tests<2, 5, int>();
    vector_matrix_tests<3, 2, int>();
    vector_matrix_tests<3, 3, int>();
    vector_matrix_tests<3, 4, int>();
    vector_matrix_tests<3, 5, int>();
    vector_matrix_tests<4, 2, int>();
    vector_matrix_tests<4, 3, int>();
    vector_matrix_tests<4, 4, int>();
    vector_matrix_tests<4, 5, int>();
    vector_matrix_tests<5, 2, int>();
    vector_matrix_tests<5, 3, int>();
    vector_matrix_tests<5, 4, int>();
    vector_matrix_tests<5, 5, int>();
    real_vector_matrix_tests<2, double>();
    real_vector_matrix_tests<3, double>();
    real_vector_matrix_tests<4, double>();
    real_vector_matrix_tests<5, double>();
  }
  timing_tests();
  std::cout << "OK" << std::endl;
  return 0;
}
