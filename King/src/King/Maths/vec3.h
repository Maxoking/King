#pragma once

namespace King {
  namespace maths {
    struct KING_API vec3 {
      float x;
      float y;
      float z;

      vec3();
      vec3(const float& x, const float& y, const float& z);
         
      vec3& add(const vec3& other);
      vec3& subtract(const vec3& other);
      vec3& multiply(const vec3& other);
      vec3& divide(const vec3& other);

      float dot(const vec3& other);

      vec3 operator+(const vec3 & right);
      vec3 operator-(const vec3& right);
      vec3 operator*(const vec3& right);
      vec3 operator/(const vec3& right);

      vec3 operator+=(const vec3& right);
      vec3 operator-=(const vec3& right);
      vec3 operator*=(const vec3& right);
      vec3 operator/=(const vec3& right);



    };

    std::ostream& operator<<(std::ostream& stream, const vec3& vec) {
      stream << "vec2: " << "(" << vec.x << " , " << vec.y << " , " << vec.z << ")";
      return stream;
    };


  }
}
