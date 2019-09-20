#ifndef GAME_MATH_SRC_VEC_HPP_INCLUDED
#define GAME_MATH_SRC_VEC_HPP_INCLUDED

#include <assert.h>
#include <cmath>
#include <stdint.h>

namespace gmath {

template <typename T, size_t N>
struct Vec {
  using type = Vec<T, N>;

  T axis[N];

  T& operator[](const size_t idx) {
    assert(idx < N);
    return this->axis[idx];
  }

  const T& operator[](const size_t idx) const {
    assert(idx < N);
    return this->axis[idx];
  }

  Vec::type operator+(const Vec::type& o) {
    Vec::type r;
    for (int i = 0; i < N; ++i) {
      r.axis[i] = this->axis[i] + o.axis[i];
    }
    return r;
  }

  Vec::type operator-(const Vec::type& o) {
    Vec::type r;
    for (int i = 0; i < N; ++i) {
      r.axis[i] = this->axis[i] - o.axis[i];
    }
    return r;
  }

  Vec::type operator*(const Vec::type& o) {
    Vec::type r;
    for (int i = 0; i < N; ++i) {
      r.axis[i] = this->axis[i] * o.axis[i];
    }
    return r;
  }

  Vec::type operator*(T scalar) {
    Vec::type r;
    for (int i = 0; i < N; ++i) {
      r.axis[i] = this->axis[i] * scalar;
    }
    return r;
  }

  T dot(const Vec::type& o) {
    float r;
    for (int i = 0; i < N; ++i) {
      r += this->axis[i] * o.axis[i];
    }
    return r;
  }

  T length() { return std::sqrt(this->dot(this)); }

  T length2() { return this->dot(this); }

  Vec::type normalize() {
    Vec::type r;
    T len;
    len = 1.0 / this->length();
    for (int i = 0; i < N; ++i) {
      r.axis[i] = this->axis[i] * len;
    }
    return r;
  }

  Vec::type cross(const Vec::type& o) {
    static_assert(N == 3, "cross is only for Vec<T,3>");
    Vec::type r;
    r.axis[0] = this->axis[1] * o.axis[2] - this->axis[2] * o.axis[1];
    r.axis[1] = this->axis[2] * o.axis[0] - this->axis[0] * o.axis[2];
    r.axis[2] = this->axis[0] * o.axis[1] - this->axis[1] * o.axis[0];
    return r;
  }

}; // struct gamth::Vec<T, N>

using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;

} // namespace gmath

#endif // GAME_MATH_SRC_VEC_HPP_INCLUDED
