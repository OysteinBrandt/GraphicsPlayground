#pragma once

#include <GL/glew.h>
#include "Engine/Render/Renderable.h"
#include "Engine/Render/OpenGL/OpenGLModel.h"
#include "Engine/DllHelper.h"

#include <Engine/Math/Vec3.h>
#include "Engine/Render/OpenGL/Shader.h"
#include <Engine/Generator/Shape.h>

#include <vector>
#include <memory>

namespace engine::render{ class Camera; }

namespace engine::render::opengl
{
  class ENGINE_API Renderer
  {
    Shader m_defaultShader;
    const Camera &m_camera;
    std::vector<std::shared_ptr<OpenGLModel>> m_models;
    std::vector<std::shared_ptr<Renderable>> m_renderables;

  public:
    Renderer(const Camera& camera, const Shader& defaultShader);
    ~Renderer();

    Renderer operator=(const Renderer&) = delete;
    Renderer& opearator(const Renderer&) = delete;

    const std::shared_ptr<OpenGLModel> add(const engine::Geometry& data, GLenum renderMode);
    const std::shared_ptr<OpenGLModel> add(const std::vector<math::Vec3>& vertices, const std::vector<unsigned short>& indices,
                                           const std::vector<math::Vec3>& colors, GLenum renderMode);

    const std::shared_ptr<Renderable> add(const OpenGLModel &model, Shader *shader = nullptr);

    void render();
  };
}