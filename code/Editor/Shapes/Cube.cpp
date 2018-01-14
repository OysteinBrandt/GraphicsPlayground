#include "Cube.h"
#include <Engine/Math/Vec3.h>

namespace shapes
{
  Cube::Cube(float size)
  {
    float dist = size / 2;
    vertices =
    {
      math::Vec3{ -dist, -dist, -dist },
      math::Vec3{  dist, -dist, -dist },
      math::Vec3{  dist,  dist, -dist },
      math::Vec3{ -dist,  dist, -dist },
      math::Vec3{  dist, -dist,  dist },
      math::Vec3{ -dist, -dist,  dist },
      math::Vec3{ -dist,  dist,  dist },
      math::Vec3{  dist,  dist,  dist }
    };

    colors =
    {
      math::Vec3{ 1, 0, 0 },
      math::Vec3{ 1, 0, 0 },
      math::Vec3{ 1, 0, 0 },
      math::Vec3{ 1, 0, 0 },
      math::Vec3{ 0, 1, 0 },
      math::Vec3{ 0, 1, 0 },
      math::Vec3{ 0, 1, 0 },
      math::Vec3{ 0, 1, 0 }

      //math::Vec3{ 84, 52, 150 },
      //math::Vec3{ 150, 236, 58 },
      //math::Vec3{ 209, 172, 77 },
      //math::Vec3{ 2, 118, 7 },
      //math::Vec3{ 51, 64, 194 },
      //math::Vec3{ 106, 3, 13 },
      //math::Vec3{ 149, 212, 55 },
      //math::Vec3{ 253, 97, 61 }
    };

    indices =
    {
      0, 2, 3,
      0, 1, 2,

      1, 7, 2,
      1, 4, 7,

      4, 6, 7,
      4, 5, 6,

      5, 3, 6,
      5, 0, 3,

      3, 7, 6,
      3, 2, 7,

      4, 0, 5,
      4, 1, 0
    };
  }
}