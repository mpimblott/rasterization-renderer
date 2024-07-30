#include "point.h"

const double pi = std::acos(-1);

inline Point3::Point3() {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
}

inline Point3::Point3(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

inline float &Point3::x() { return data[0]; }

inline float &Point3::y() { return data[1]; }

inline float &Point3::z() { return data[2]; }

inline const float &Point3::x() const { return data[0]; }

inline const float &Point3::y() const { return data[1]; }

inline const float &Point3::z() const { return data[2]; }

inline Point3 &Point3::operator=(const Point3 &v) {
    for (size_t i = 0; i < 3; i++) {
        data[i] = v[i];
    }
    return *this;
}

inline Point3 &Point3::operator=(const Vec<float, 3> &v) {
    for (size_t i = 0; i < 3; i++) {
        data[i] = v[i];
    }
    return *this;
}

inline Point3h::Point3h() { data[3] = 1; }

inline Point3h::Point3h(std::initializer_list<float> v) {
    assert(v.size() == 3 && "Vector initialiser list has incorrect size.");
    std::copy(v.begin(), v.end(), data.begin());
    data[3] = 1;
}

inline Point3h::Point3h(Vec<float, 4> &v) {
    data[0] = v[0];
    data[1] = v[1];
    data[2] = v[2];
    data[3] = 1;
}

inline Point3h::Point3h(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 1;
}

inline Point3h::Point3h(float x, float y, float z, float w) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}

inline float &Point3h::x() { return data[0]; }

inline float &Point3h::y() { return data[1]; }

inline float &Point3h::z() { return data[2]; }

inline const float &Point3h::x() const { return data[0]; }

inline const float &Point3h::y() const { return data[1]; }

inline const float &Point3h::z() const { return data[2]; }

inline float Point3h::norm() const { return sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2)); }

inline Point3h &Point3h::normalise() {
    float n = norm();
    data[0] /= n;
    data[1] /= n;
    data[2] /= n;
    return *this;
}

inline Point3h Point3h::normalise() const {
    float n = norm();
    return Point3h({data[0] / n, data[1] / n, data[2] / n});
}

inline Point3h rotate_x(Point3h &v, float angle) {
    Matf4 m = {{1, 0, 0, 0},
               {0, static_cast<float>(cos(angle)), static_cast<float>(-1 * sin(angle)), 0},
               {0, static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0},
               {0, 0, 0, 1}};
    auto k = m * transpose(v);
    return e1h;
}

inline Point3h &Point3h::operator=(const Point3h &v) {
    for (size_t i = 0; i < 3; i++) {
        data[i] = v[i];
    }
    return *this;
}

inline Point3h Point3h::operator+(const Point3h &v) const {
    return Point3h(data[0] + v[0], data[1] + v[1], data[2] + v[2]);
}

inline Point3h Point3h::operator-(const Point3h &v) const {
    return Point3h(data[0] - v[0], data[1] - v[1], data[2] - v[2]);
}

inline Point3h operator*(float lhs, const Point3h &rhs) { return Point3h(rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs); }

inline Point3h operator*(const Point3h &lhs, float rhs) { return Point3h(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs); }

inline Point3h operator*(const Point3h &lhs, const Matf4 &rhs) {
    float x = lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0] + lhs[2] * rhs[2][0] + rhs[3][0];
    float y = lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1] + lhs[2] * rhs[2][1] + rhs[3][1];
    float z = lhs[0] * rhs[0][2] + lhs[1] * rhs[1][2] + lhs[2] * rhs[2][2] + rhs[3][2];
    float w = lhs[0] * rhs[0][3] + lhs[1] * rhs[1][3] + lhs[2] * rhs[2][3] + rhs[3][3];
    if (w != 1) {
        x /= w;
        y /= w;
        z /= w;
    }
    return Point3h(x, y, z);
}

inline Point3h cross(const Point3h &lhs, const Point3h &rhs) {
    float a = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    float b = lhs[0] * rhs[2] - lhs[2] * rhs[0];
    float c = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Point3h(a, -b, c);
}
