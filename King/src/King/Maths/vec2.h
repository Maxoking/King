#pragma once

namespace King {
  namespace maths {
    struct KING_API vec2 {
      float x;
      float y;

      vec2();
      vec2(const float& x, const float& y);

      vec2& add(const vec2& other);
      vec2& subtract(const vec2& other);
      vec2& multiply(const vec2& other);
      vec2& divide(const vec2& other);

      float dot(const vec2& other);

      vec2 operator+(const vec2 & right);
      vec2 operator-(const vec2& right);
      vec2 operator*(const vec2& right);
      vec2 operator/(const vec2& right);

      vec2 operator+=(const vec2& right);
      vec2 operator-=(const vec2& right);
      vec2 operator*=(const vec2& right);
      vec2 operator/=(const vec2& right);
      
      

    };

    std::ostream& operator<<(std::ostream& stream, const vec2& vec) {
      stream << "vec2: " << "(" << vec.x << ", " << vec.y << ")";
      return stream;
    };


}}
