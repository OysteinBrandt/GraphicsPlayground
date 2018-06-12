#pragma once

#include <GL/glew.h>
#include "Engine/Render/Renderable.h"
#include "Engine/Render/OpenGL/OpenGLModel.h"
#include "Engine/DllHelper.h"

#include <Engine/Math/Vec3.h>
#include <Engine/Math/Vec2.h>
#include "Engine/Render/OpenGL/Shader.h"
#include <Engine/Generator/Shape.h>

#include <vector>
#include <memory>

namespace engine::render{ class Camera; }

namespace engine::render::opengl
{
  class Renderer
  {
    Shader m_defaultShader;
    const Camera &m_camera;
    std::vector<std::shared_ptr<OpenGLModel>> m_models;
    std::vector<std::shared_ptr<Renderable>> m_renderables; // Multiple renderables can refer to the same model

  public:
    ENGINE_API Renderer(const Camera& camera, const Shader& defaultShader);
    ENGINE_API ~Renderer();

    Renderer operator=(const Renderer&) = delete;
    Renderer& opearator(const Renderer&) = delete;

    ENGINE_API const std::shared_ptr<OpenGLModel> add(const engine::Geometry& data, GLenum renderMode);
    ENGINE_API const std::shared_ptr<OpenGLModel> add(const std::vector<math::Vec3>& vertices, const std::vector<unsigned short>& indices,
                                           const std::vector<math::Vec3>& colors, const std::vector<math::Vec2>& textureCoords, GLenum renderMode);

    ENGINE_API const std::shared_ptr<Renderable> add(const OpenGLModel &model, Shader *shader = nullptr);

    ENGINE_API void render();
  };
}