#include "Mat4.h"
#include <cmath>

// TODO (obr): Replace cassert with platform independent assert
#include <cassert>

namespace math
{
	Mat4 Mat4::rotate(float radians, Axis axis)
	{
		auto cosine = cos(radians);
		auto sine = sin(radians);

		switch (axis)
		{
		case Mat4::Axis::X:
			return Mat4{1,			0,		 0, 0,
									0, cosine, -sine, 0,
									0, sine, cosine,  0,
									0,			0,		 0, 1};
			break;

		case Mat4::Axis::Y:
			return Mat4{ cosine, 0,   sine, 0,
												0, 1,		   0, 0,
									  -sine, 0, cosine, 0,
												0, 0,			 0, 1};
			break;

		case Mat4::Axis::Z:
			return Mat4{ cosine, -sine, 0, 0,
									 sine,  cosine, 0, 0,
									 0,         0,  1, 0,
									 0,         0,  0, 1};
			break;

		default:
			assert("Not a valid axis!");
			return Mat4();
			break;
		}
	}

	/*********************************************************/

	Mat4 Mat4::rotate(float radians, const Vec3 & axis)
	{
		auto cosine = cos(radians);
		auto c = 1 - cosine;
		auto sine = sin(radians);

		return Mat4{ axis.x*axis.x*c+cosine,      axis.x*axis.y*c-axis.z*sine, axis.x*axis.z*c+axis.y*sine, 0.f,
								 axis.x*axis.y*c+axis.z*sine, axis.y*axis.y*c+cosine,      axis.y*axis.z*c-axis.x*sine, 0.f,
								 axis.x*axis.z*c-axis.y*sine, axis.y*axis.z*c+axis.x*sine, axis.z*axis.z*c+cosine,      0.f,
								 0.f,                         0.f,                         0.f,                         1.f};
	}
}