#include "kngpch.h"
#include "vec3.h"

namespace King {
  namespace maths {
    vec3::vec3()
    {
      this->x = 0.f;
      this->y = 0.f;
      this->z = 0.f;
    }

    vec3::vec3(const float& x, const float& y, const float& z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    vec3& vec3::add(const vec3& other)
    {
      this->x += other.x;
      this->y += other.y;
      this->z += other.z;

      return *this;
    }

    vec3& vec3::subtract(const vec3& other)
    {
      this->x -= other.x;
      this->y -= other.y;
      this->z -= other.z;

      return *this;
    }

    vec3& vec3::multiply(const vec3& other)
    {
      this->x *= other.x;
      this->y *= other.y;
      this->z *= other.z;

      return *this;
    }

    vec3& vec3::divide(const vec3& other)
    {
      this->x /= other.x;
      this->y /= other.y;
      this->z /= other.z;

      return *this;
    }

    float vec3::dot(const vec3& other) {
      return this->x * other.x + this->y * other.y + this->z * other.z;
    }



    vec3 vec3::operator+(const vec3& right)
    {
      vec3 vec;
      vec.x = this->x + right.x;
      vec.y = this->y + right.y;
      vec.y = this->z + right.z;
      return vec;
    }
    vec3 vec3::operator-(const vec3& right)
    {
      vec3 vec;
      vec.x = this->x - right.x;
      vec.y = this->y - right.y;
      vec.y = this->z - right.z;
      return vec;
    }

    vec3 vec3::operator*(const vec3& right)
    {
      vec3 vec;
      vec.x = this->x * right.x;
      vec.y = this->y * right.y;
      vec.y = this->z * right.z;
      return vec;
    }

    vec3 vec3::operator/(const vec3& right)
    {
      vec3 vec;
      vec.x = this->x / right.x;
      vec.y = this->y / right.y;
      vec.y = this->z / right.z;
      return vec;
    }

    vec3 vec3::operator+=(const vec3& right)
    {
      return this->add(right);
    }

    vec3 vec3::operator-=(const vec3& right)
    {
      return this->subtract(right);
    }

    vec3 vec3::operator*=(const vec3& right)
    {
      return this->multiply(right);
    }

    vec3 vec3::operator/=(const vec3& right)
    {
      return this->divide(right);
    }

  }
}