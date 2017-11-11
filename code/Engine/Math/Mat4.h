#pragma once

#include "Vec3.h"
#include <array>
#include "DllHelper.h"

namespace math
{
	class Mat4
	{
	public:

		enum class Axis { X, Y, Z };

		std::array<float, 4> x{ 1.0f, 0.0f, 0.0f, 0.0f };
		std::array<float, 4> y{ 0.0f, 1.0f, 0.0f, 0.0f };
		std::array<float, 4> z{ 0.0f, 0.0f, 1.0f, 0.0f };
		std::array<float, 4> w{ 0.0f, 0.0f, 0.0f, 1.0f };

		inline Mat4 (float x1, float y1, float z1, float w1,
								 float x2, float y2, float z2, float w2,
								 float x3, float y3, float z3, float w3,
								 float x4, float y4, float z4, float w4)
			: x { x1, x2, x3, x4 }, y { y1, y2, y3, y4 },
			  z { z1, z2, z3, z4 }, w { w1, w2, w3, w4 }
		{ }

		inline Mat4()
		{ }

		// TODO (obr): Replace enum with a unit vector? (eg. rotate around a custom axis)
		OBR_API static Mat4 rotate(float radians, Axis axis);

		OBR_API static Mat4 rotate(float radians, const Vec3 &axis);

		inline static Mat4 translate(float x, float y, float z)
		{
			return Mat4{ 1, 0, 0, x,
									 0, 1, 0, y,
									 0, 0, 1, z,
									 0, 0, 0, 1 };
		}

		inline static Mat4 translate(const Vec3 &vec)
		{
			return translate(vec.x, vec.y, vec.z);
		}

		inline static Mat4 scale(float x, float y, float z) {
			return Mat4{ x, 0, 0, 0,
									 0, y, 0, 0,
									 0, 0, z, 0,
									 0, 0, 0, 1 };
		}

	};

	inline Vec3 operator*(const Mat4& mat, const Vec3 &vec) {
		return Vec3{ mat.x[0] * vec.x + mat.y[0] * vec.y + mat.z[0] * vec.z + 1 * mat.w[0],
								 mat.x[1] * vec.x + mat.y[1] * vec.y + mat.z[1] * vec.z + 1 * mat.w[1],
								 mat.x[2] * vec.x + mat.y[2] * vec.y + mat.z[2] * vec.z + 1 * mat.w[2] };
	}

	inline Mat4 operator*(const Mat4 &first, const Mat4 &second) {
		return Mat4
		{
			first.x[0] * second.x[0] + first.y[0] * second.x[1] + first.z[0] * second.x[2] + first.w[0] * second.x[3],
			first.x[0] * second.y[0] + first.y[0] * second.y[1] + first.z[0] * second.y[2] + first.w[0] * second.y[3],
			first.x[0] * second.z[0] + first.y[0] * second.z[1] + first.z[0] * second.z[2] + first.w[0] * second.z[3],
			first.x[0] * second.w[0] + first.y[0] * second.w[1] + first.z[0] * second.w[2] + first.w[0] * second.w[3],

			first.x[1] * second.x[0] + first.y[1] * second.x[1] + first.z[1] * second.x[2] + first.w[1] * second.x[3],
			first.x[1] * second.y[0] + first.y[1] * second.y[1] + first.z[1] * second.y[2] + first.w[1] * second.y[3],
			first.x[1] * second.z[0] + first.y[1] * second.z[1] + first.z[1] * second.z[2] + first.w[1] * second.z[3],
			first.x[1] * second.w[0] + first.y[1] * second.w[1] + first.z[1] * second.w[2] + first.w[1] * second.w[3],

			first.x[2] * second.x[0] + first.y[2] * second.x[1] + first.z[2] * second.x[2] + first.w[2] * second.x[3],
			first.x[2] * second.y[0] + first.y[2] * second.y[1] + first.z[2] * second.y[2] + first.w[2] * second.y[3],
			first.x[2] * second.z[0] + first.y[2] * second.z[1] + first.z[2] * second.z[2] + first.w[2] * second.z[3],
			first.x[2] * second.w[0] + first.y[2] * second.w[1] + first.z[2] * second.w[2] + first.w[2] * second.w[3],

			first.x[3] * second.x[0] + first.y[3] * second.x[1] + first.z[3] * second.x[2] + first.w[3] * second.x[3],
			first.x[3] * second.y[0] + first.y[3] * second.y[1] + first.z[3] * second.y[2] + first.w[3] * second.y[3],
			first.x[3] * second.z[0] + first.y[3] * second.z[1] + first.z[3] * second.z[2] + first.w[3] * second.z[3],
			first.x[3] * second.w[0] + first.y[3] * second.w[1] + first.z[3] * second.w[2] + first.w[3] * second.w[3]
		};
	}
}