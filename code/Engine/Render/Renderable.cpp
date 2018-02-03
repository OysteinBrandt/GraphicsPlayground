#include "Renderable.h"
#include "Engine/Render/OpenGL/Shader.h"

namespace engine::render
{

  const opengl::Shader* Renderable::customShader() const
  {
    return m_customShader;
  }

}