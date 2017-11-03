#pragma once

#include <memory>
#include <Math/Mat4.h>

namespace engine::render
{
	class Geometry;
	class Shader;
	class Renderable
	{
		const Geometry &m_geometry;
		const Shader *m_shader;
	public:
		math::Mat4 m_matrix;

		Renderable(const Geometry &geometry, const Shader *shader = nullptr)
			: m_geometry(geometry), m_shader(shader)
		{ }

		Renderable operator=(const Renderable&) = delete;
		Renderable& opearator(const Renderable&) = delete;

		const Geometry& geometry() const
		{
			return m_geometry;
		}

		const Shader* shader() const;
	};
}