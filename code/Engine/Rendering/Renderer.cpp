#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "OpenGLModel.h"

#include <cassert> //TODO: Replace
namespace engine::render
{

	static const int NUM_MAX_MODELS = 1;

Renderer::Renderer(const Camera &camera, const Shader &defaultShader) : m_camera(camera), m_defaultShader(defaultShader)
{

	// TODO: Find a solution to the problem of returning pointer/reference to vector elements, as they will be invalidated when the size increases!!!
	m_models.reserve(NUM_MAX_MODELS);  // TODO: This is a temp solution
	m_renderables.reserve(NUM_MAX_MODELS); // TODO: This is a temp solution

	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
}

OpenGLModel* Renderer::addGeometry(const std::vector<math::Vec3> &vertices, const std::vector<unsigned short> &indices, GLenum renderMode)
{
	assert(m_models.size() < NUM_MAX_MODELS);
	// TODO: Find a solution to the problem of returning pointer/reference to vector elements, as they will be invalidated when the size increases!!!
	return &m_models.emplace_back(vertices, indices, renderMode);
}

Renderable* Renderer::addRenderable(OpenGLModel *model, Shader *shader)
{
	return &m_renderables.emplace_back(*model, shader);
}

void Renderer::render(float width, float height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &renderable : m_renderables)
	{
		const auto& model = renderable.model();
		glBindVertexArray(model.vaoID());
		glEnableVertexAttribArray(0);

		const auto* shader = renderable.shader();
		if (shader == nullptr)
			shader = &m_defaultShader;

		shader->bind();
		const math::Mat4 MVP = m_camera.projectionMatrix() * m_camera.viewMatrix() * renderable.m_matrix;
		shader->loadMatrix(MVP);
		shader->loadColor(math::Vec3{ 1.0f, 0.0f, 0.0f });

		glDrawElements(model.renderMode(), model.vertexCount(), GL_UNSIGNED_SHORT, 0);

		if (model.renderOutline())
		{
			shader->loadColor(math::Vec3{ 0.0f, 1.0f, 0.0f });
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glPolygonOffset(0.f, -0.5f);	// TODO: Calculate suitable offset
			glDrawElements(model.renderMode(), model.vertexCount(), GL_UNSIGNED_SHORT, 0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		if (shader != nullptr)
			shader->unbind();
	}
}

}