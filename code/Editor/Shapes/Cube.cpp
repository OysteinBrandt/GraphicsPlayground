#include "Cube.h"
#include <Math/Vec3.h>

namespace editor
{
	Cube::Cube(float size)
	{
		float dist = size / 2;
		vertices =
		{
			math::Vec3{ -dist,  0.f,  0.f },
			math::Vec3{  dist,  0.f,  0.f },
			math::Vec3{  dist, dist,  0.f },
			math::Vec3{ -dist, dist,  0.f },
			math::Vec3{  dist,  0.f, dist },
			math::Vec3{ -dist,  0.f, dist },
			math::Vec3{ -dist, dist, dist },
			math::Vec3{  dist, dist, dist }
		};

		indices =
		{
			0, 2, 3,
			0, 1, 2,
			
			1, 7, 2,
			1, 4, 7,

			4, 6, 7,
			4, 5, 6,

			5, 3, 6,
			5, 0, 3,

			3, 7, 6,
			3, 2, 7,

			4, 0, 5,
			4, 1, 0
		};
	}
}