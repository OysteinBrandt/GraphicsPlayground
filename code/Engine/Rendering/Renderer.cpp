#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "OpenGLModel.h"

namespace engine::render
{

Renderer::Renderer(const Camera &camera, const Shader &defaultShader) : m_camera(camera), m_defaultShader(defaultShader)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

size_t Renderer::addGeometry(const std::vector<math::Vec3> &vertices, const std::vector<unsigned short> &indices,
	const std::vector<math::Vec3> &colors, GLenum renderMode)
{
	m_models.emplace_back(vertices, indices, colors, renderMode);
	return m_models.size()-1;
}

size_t Renderer::addRenderable(size_t modelId, Shader *shader)
{
	m_renderables.emplace_back(m_models[modelId], shader);
	return m_renderables.size()-1;
}

OpenGLModel* Renderer::getModel(size_t geometryId)
{
	return &m_models.at(geometryId);
}

Renderable* Renderer::getRenderable(size_t id)
{
	return &m_renderables.at(id);
}

void Renderer::render(float width, float height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &renderable : m_renderables)
	{
		const auto& model = renderable.model();
		model.bind();

		const auto* shader = renderable.shader();
		if (shader == nullptr)
			shader = &m_defaultShader;

		shader->bind();
		const math::Mat4 MVP = m_camera.projectionMatrix() * m_camera.viewMatrix() * renderable.m_matrix;
		shader->loadMatrix(MVP);
		

		glDrawElements(model.renderMode(), model.vertexCount(), GL_UNSIGNED_SHORT, 0);

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