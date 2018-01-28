#include "Positional.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Entities/Entity.h"

namespace entities::component
{

  void Positional::assign(engine::render::Renderable* const renderable)
  {
    m_renderable = renderable;
  }

  void Positional::update(float)
  {
    if (!m_renderable)
    {
      // TODO: Assert error
      return;
    }

    if (auto const parent = getParent())
    {
      m_renderable->m_matrix = math::Mat4::translate(parent->position) *
        math::Mat4::rotate(parent->orientation, math::Mat4::Axis::Z);
    }
    else
    {
      // TODO: Assert error
    }
  }

  void Positional::position(const math::Vec3 &pos) const
  {
    auto const parent = getParent();
    if (!parent)
    {
      // TODO: Assert error
      return;
    }

    getParent()->position = pos;
  }

}