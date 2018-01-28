#include "Renderer.h"
#include "Engine/Rendering/Camera.h"
#include "Engine/Rendering/OpenGLModel.h"

namespace engine::render
{

  Renderer::Renderer(const Camera& camera, const Shader& defaultShader) : m_camera(camera), m_defaultShader(defaultShader)
  {
    m_defaultShader.initialize();
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);	// TODO: Make sure all models are rendered with the correct winding order
    glPointSize(3.f);
  }

  Renderer::~Renderer()
  {
  }

  const std::shared_ptr<OpenGLModel> Renderer::add(const engine::Geometry& data, GLenum renderMode)
  {
    return add(data.vertices, data.indices, data.colors, renderMode);
  }

  const std::shared_ptr<OpenGLModel> Renderer::add(const std::vector<math::Vec3>& vertices, const std::vector<unsigned short>& indices,
                                                   const std::vector<math::Vec3>& colors, GLenum renderMode)
  {
    return m_models.emplace_back(std::make_shared<OpenGLModel>(vertices, indices, colors, renderMode));
  }

  const std::shared_ptr<Renderable> Renderer::add(const OpenGLModel &model, Shader *shader)
  {
    return m_renderables.emplace_back(std::make_shared<Renderable>(model, shader));
  }

  void Renderer::render()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto &renderable : m_renderables)
    {
      const auto& model = renderable->model();
      model.bind();

      const auto* shader = renderable->customShader();
      if (shader == nullptr)
        shader = &m_defaultShader;

      shader->bind();
      const math::Mat4 MVP = m_camera.projectionMatrix() * m_camera.viewMatrix() * renderable->m_matrix;
      shader->loadMatrix(MVP);

      if (model.usesIndices())
        glDrawElements(model.renderMode(), model.vertexCount(), GL_UNSIGNED_SHORT, 0);
      else
        glDrawArrays(model.renderMode(), 0, model.vertexCount());

#if 0	// TODO: Allow custom color??
      if (model.renderOutline())
      {
        shader->loadColor(math::Vec3{ 0.0f, 1.0f, 0.0f });
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonOffset(0.f, -0.5f);	// TODO: Calculate suitable offset
        glDrawElements(model.renderMode(), model.vertexCount(), GL_UNSIGNED_SHORT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
#endif

      model.unbind();

      if (shader != nullptr)
        shader->unbind();
    }
  }

}