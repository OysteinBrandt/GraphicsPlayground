#pragma once

#include "Engine/Entities/Component.h"

namespace engine::render { class Renderable; }
namespace math { class Vec3; }

namespace entities::component
{
  class ENGINE_API Positional : public Component
  {
    engine::render::Renderable* m_renderable;

  public:

    Positional(engine::render::Renderable* const renderable) : m_renderable(renderable)
    { }

    void assign(engine::render::Renderable* const renderable);
    void update(float dt) override;
    void position(const math::Vec3 &pos) const;
  };
}