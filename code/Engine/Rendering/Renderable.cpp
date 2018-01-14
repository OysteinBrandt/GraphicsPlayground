#include "Renderable.h"
#include "Engine/Rendering/Shader.h"

namespace engine::render
{

  const Shader* Renderable::customShader() const
  {
    return m_customShader;
  }

}