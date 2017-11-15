#pragma once

#include <memory>
#include <Math/Mat4.h>

namespace engine::render
{
	class OpenGLModel;
	class Shader;
	class Renderable
	{
		const OpenGLModel &m_model;
		const Shader *m_customShader;
	public:
		math::Mat4 m_matrix;

		Renderable(const OpenGLModel &model, const Shader *shader = nullptr)
			: m_model(model), m_customShader(shader)
		{ }

		Renderable operator=(const Renderable&) = delete;
		Renderable& opearator(const Renderable&) = delete;

		const OpenGLModel& model() const
		{
			return m_model;
		}

		const Shader* shader() const;
	};
}