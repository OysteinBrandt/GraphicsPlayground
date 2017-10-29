#pragma once

#include <vector>

namespace math { class Vec3; }

namespace engine::render
{
	class Geometry
	{
	private:
		const std::vector<math::Vec3> &m_vertices;
		const std::vector<unsigned short> &m_indices;
		GLenum m_renderMode;

	public:

		Geometry(const std::vector<math::Vec3> &vertices,
						 const std::vector<unsigned short> &indices,
						 GLenum renderMode)
			: m_vertices(vertices), 
				m_indices(indices), 
				m_renderMode(renderMode)
		{ }

		const std::vector<math::Vec3> &vertices() const
		{
			return m_vertices;
		}

		const std::vector<unsigned short> &indices() const
		{
			return m_indices;
		}

		GLenum renderMode() const
		{
			return m_renderMode;
		}
	};
}