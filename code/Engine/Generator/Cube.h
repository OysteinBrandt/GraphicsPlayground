#pragma once

#include "Shape.h"
#include <Engine/DllHelper.h>

namespace engine::generator
{
  class ENGINE_API Cube : public Shape
  {
  private:
    float m_size;
  public:

    Cube(float size = 1.f);

    Geometry generate() const;
  };
}