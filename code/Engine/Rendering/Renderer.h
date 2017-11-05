#pragma once

#include <GL/glew.h>
#include "Renderable.h"
#include <vector>
#include "DllHelper.h"

#include <Math/Vec3.h>

namespace engine::render
{
	class Shader;
	class Camera;
	class OBR_API Renderer
	{
		const Shader &m_defaultShader;
		const Camera &m_camera;
		std::vector<OpenGLModel> m_models;
		std::vector<Renderable> m_renderables;

	public:
		Renderer(const Camera &camera, const Shader &defaultShader);
		~Renderer();

		Renderer operator=(const Renderer&) = delete;
		Renderer& opearator(const Renderer&) = delete;

		OpenGLModel* addGeometry(const std::vector<math::Vec3> &vertices, const std::vector<unsigned short> &indices, GLenum renderMode);
		Renderable* addRenderable(OpenGLModel *model, Shader *shader = nullptr);

		void render(float width, float height);
	};
}