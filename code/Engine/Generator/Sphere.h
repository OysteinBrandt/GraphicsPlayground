#pragma once

#include "Shape.h"
#include "Engine/Math/Vec2.h"
#include "Engine/Math/Vec3.h"
#include "Engine/DllHelper.h"

#include <vector>

namespace engine::generator
{
	struct SphereGeometry
	{
		std::vector<math::Vec3> vertices;
		std::vector<unsigned short> indices;
		std::vector<math::Vec3> normals;
		std::vector<math::Vec3> colors;
		std::vector<math::Vec2> textureCoords;
	};


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

		SphereGeometry generate(unsigned int precision)
		{
			return generate(precision, precision);
		}

		SphereGeometry generate(unsigned int widthPrecision, unsigned int heightPrecision);
	};
}