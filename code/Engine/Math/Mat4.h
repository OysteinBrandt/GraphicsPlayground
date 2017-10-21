#pragma once

namespace math
{
	class Mat4
	{
	private:

		//Vec4 vec1;
		//Vec4 vec2;
		//Vec4 vec3;
		float x1, y1, z1, w1;
		float x2, y2, z2, w2;
		float x3, y3, z3, w3;

		inline explicit Mat4 (float x1 = 1.f, float y1 = 0.f, float z1 = 0.f, float w1 = 0.f,
													float x2 = 0.f, float y2 = 1.f, float z2 = 0.f, float w2 = 0.f,
													float x3 = 0.f, float y3 = 0.f, float z3 = 1.f, float w3 = 0.f)
			//: x1(x1), y1(y1), z1(z1),
			//x2(x2), y2(y2), z2(z2),
			//x3(x3), y3(y3), z3(z3)
		{ }

	};
}