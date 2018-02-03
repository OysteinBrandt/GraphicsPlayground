#pragma once

#include <Engine/Math/Mat4.h>

namespace engine::render
{
  namespace opengl { class OpenGLModel; }
  namespace opengl { class Shader; }
  class Renderable
  {
    const opengl::OpenGLModel &m_model;
    const opengl::Shader *m_customShader;
  public:
    math::Mat4 m_matrix;

    Renderable(const opengl::OpenGLModel &model, const opengl::Shader *shader = nullptr)
      : m_model(model), m_customShader(shader)
    { }

    Renderable operator=(const Renderable&) = delete;
    Renderable& opearator(const Renderable&) = delete;

    const opengl::OpenGLModel& model() const
    {
      return m_model;
    }

    const opengl::Shader* customShader() const;
  };
}