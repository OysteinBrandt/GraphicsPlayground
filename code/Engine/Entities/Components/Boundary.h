#pragma once

#include "Engine/Entities/Component.h"
#include "Engine/Math/Vec3.h"
#include <vector>

namespace entities::component
{
  class Physics;
  class ENGINE_API Boundary : public Component
  {
    Physics &m_physics;
    math::Vec3 prevFramePos;
    const std::vector<math::Vec3> &m_boundary;

  public:
    Boundary(Physics &physicsComp, const std::vector<math::Vec3> &boundary);
    void update(float dt) override;

  };
}
