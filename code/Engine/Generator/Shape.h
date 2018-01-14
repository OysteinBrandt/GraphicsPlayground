#pragma once

#include "Engine/Math/Vec2.h"
#include "Engine/Math/Vec3.h"

#include <vector>

namespace engine
{
  struct Geometry
  {
    std::vector<math::Vec3> vertices;
    std::vector<unsigned short> indices;
    std::vector<math::Vec3> normals;
    std::vector<math::Vec3> colors;
    std::vector<math::Vec2> textureCoords;
  };

  class Shape
  {
  };
}