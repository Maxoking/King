#include "kngpch.h"

#include "vec2.h"


namespace King {
  namespace maths {
    vec2::vec2()
    {
      this->x = 0.f;
      this->y = 0.f;
    }

    vec2::vec2(const float& x, const float& y)
    {
      this->x = x;
      this->y = y;
    }

    vec2& vec2::add(const vec2& other)
    {
      this->x += other.x;
      this->y += other.y;

      return *this;
    }

    vec2& vec2::subtract(const vec2& other)
    {
      this->x -= other.x;
      this->y -= other.y;

      return *this;
    }

    vec2& vec2::multiply(const vec2& other)
    {
      this->x *= other.x;
      this->y *= other.y;

      return *this;
    }

    vec2& vec2::divide(const vec2& other)
    {
      this->x /= other.x;
      this->y /= other.y;

      return *this;
    }

    float vec2::dot(const vec2& other) {
      return this->x * other.x + this->y * other.y;
    }



    vec2 vec2::operator+(const vec2& right)
    {
      vec2 vec;
      vec.x = this->x + right.x;
      vec.y = this->y + right.y;
      return vec;
    }
    vec2 vec2::operator-(const vec2& right)
    {
      vec2 vec;
      vec.x = this->x - right.x;
      vec.y = this->y - right.y;
      return vec;
    }

    vec2 vec2::operator*(const vec2& right)
    {
      vec2 vec;
      vec.x = this->x * right.x;
      vec.y = this->y * right.y;
      return vec;
    }

    vec2 vec2::operator/(const vec2& right)
    {
      vec2 vec;
      vec.x = this->x / right.x;
      vec.y = this->y / right.y;
      return vec;
    }

    vec2 vec2::operator+=(const vec2& right)
    {
      return this->add(right);
    }

    vec2 vec2::operator-=(const vec2& right)
    {
      return this->subtract(right);
    }

    vec2 vec2::operator*=(const vec2& right)
    {
      return this->multiply(right);
    }

    vec2 vec2::operator/=(const vec2& right)
    {
      return this->divide(right);
    }
    
  }}