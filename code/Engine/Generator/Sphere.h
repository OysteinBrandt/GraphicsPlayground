#pragma once

#include "Shape.h"
#include "Engine/DllHelper.h"

namespace engine::generator
{
	// TODO: UVSphere and IcoSphere, ref. http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	// Consider subdivide Octahedron and extrude points with radius like in master thesis
	class OBR_API Sphere : public Shape
	{
		float m_radius;

	public:

		Sphere(float radius) : m_radius(radius)
		{ }

		Sphere() : m_radius{1.f}
		{ }

		float radius() const
		{
			return m_radius;
		}

		Geometry generate(unsigned int precision)
		{
			return generate(precision, precision);
		}

		Geometry generate(unsigned int widthPrecision, unsigned int heightPrecision);
	};
}