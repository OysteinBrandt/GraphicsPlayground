#pragma once

#include "Shape.h"
#include <Engine/DllHelper.h>
#include <Engine/Render/Color.h>

namespace engine::generator
{
  class ENGINE_API Cube : public Shape
  {
  private:
    float m_size;
    math::Vec3 m_color;

  public:

    Cube(float size = 1.f, const math::Vec3& color = color::White);

    Geometry generate() const;
  };
}