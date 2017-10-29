#pragma once

#include <memory>
#include <Math/Mat3.h>

namespace engine::render
{
	class Geometry;
	class Renderable
	{
		const Geometry& m_geometry;
	public:
		math::Mat3 m_matrix;

		Renderable(const Geometry &geometry)
			: m_geometry(geometry)
		{ }

		Renderable operator=(const Renderable&) = delete;
		Renderable& opearator(const Renderable&) = delete;

		const Geometry& geometry() const
		{
			return m_geometry;
		}
	};
}