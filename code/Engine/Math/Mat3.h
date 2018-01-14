#pragma once

#include "Vec3.h"
#include "Vec2.h"
#include "Engine/DllHelper.h"

namespace math {

  class Mat3
  {
  public:

    enum class Axis
    {
      X, Y, Z
    };

    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;

    inline explicit Mat3(float x1 = 1.f, float y1 = 0.f, float z1 = 0.f,
      float x2 = 0.f, float y2 = 1.f, float z2 = 0.f,
      float x3 = 0.f, float y3 = 0.f, float z3 = 1.f)
      : x1(x1), y1(y1), z1(z1),
      x2(x2), y2(y2), z2(z2),
      x3(x3), y3(y3), z3(z3)
    { }

    inline Vec3 operator*(const Vec3 &vec) const {
      return Vec3(x1 * vec.x + y1 * vec.y + z1 * vec.z,
        x2 * vec.x + y2 * vec.y + z2 * vec.z,
        x3 * vec.x + y3 * vec.y + z3 * vec.z);
    }

    // TODO (obr): Replace enum with a unit vector? (eg. rotate around a custom axis)
    OBR_API static Mat3 rotate(float radians, Axis axis);

    inline static Mat3 translate(float x, float y)
    {
      return Mat3{ 1, 0, x,
                    0, 1, y,
                    0, 0, 1 };
    }

    inline static Mat3 translate(const Vec2 &position)
    {
      return translate(position.x, position.y);
    }

    inline static Mat3 translate(const Vec3 &position)
    {
      return translate(position.x, position.y);
    }

    inline static Mat3 scale(float x, float y) {
      return Mat3{ x, 0, 0,
                   0, y, 0,
                   0, 0, 1 };
    }
  };

  inline Mat3 operator*(const Mat3 &lhs, const Mat3 &rhs) {
    return Mat3{
      lhs.x1 * rhs.x1 + lhs.y1 * rhs.x2 + lhs.z1 * rhs.x3,
      lhs.x1 * rhs.y1 + lhs.y1 * rhs.y2 + lhs.z1 * rhs.y3,
      lhs.x1 * rhs.z1 + lhs.y1 * rhs.z2 + lhs.z1 * rhs.z3,

      lhs.x2 * rhs.x1 + lhs.y2 * rhs.x2 + lhs.z2 * rhs.x3,
      lhs.x2 * rhs.y1 + lhs.y2 * rhs.y2 + lhs.z2 * rhs.y3,
      lhs.x2 * rhs.z1 + lhs.y2 * rhs.z2 + lhs.z2 * rhs.z3,

      lhs.x3 * rhs.x1 + lhs.y3 * rhs.x2 + lhs.z3 * rhs.x3,
      lhs.x3 * rhs.y1 + lhs.y3 * rhs.y2 + lhs.z3 * rhs.y3,
      lhs.x3 * rhs.z1 + lhs.y3 * rhs.z2 + lhs.z3 * rhs.z3,

    };
  }
}
