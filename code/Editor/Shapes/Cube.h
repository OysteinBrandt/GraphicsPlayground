#pragma once

#include <Math/Vec3.h>
#include <vector>

namespace shapes
{
	class Cube
	{
	public:
		std::vector<math::Vec3> vertices;
		std::vector<unsigned short> indices;

		Cube(float size = 1.f);
	};
}