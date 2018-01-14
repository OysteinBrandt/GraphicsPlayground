#pragma once

#include "Vec2.h"
#include "Engine/DllHelper.h"

namespace math
{
  class Mat2
  {
  public:

    float x1, y1;
    float x2, y2;

    inline explicit Mat2(float x1 = 1.f, float y1 = 0.f, float x2 = 0.f, float y2 = 1.f) : x1(x1), y1(y1), x2(x2), y2(y2)
    { }

    inline Vec2 operator*(const Vec2 &vec) {
      return Vec2(x1 * vec.x + y1 * vec.y, x2 * vec.x + y2 * vec.y);
    }

    OBR_API static Mat2 rotate(float radians);

  };
}