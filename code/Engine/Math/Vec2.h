#pragma once

namespace math {

	class Vec2
	{
	public:

		float x;
		float y;
		
		Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y)
		{}

		//-----------------------------------------------

		inline void operator+=(const Vec2 &other){
			x += other.x;
			y += other.y;
		}
	};

	/***********************************************************/

	inline Vec2 operator+(const Vec2 &lhs, const Vec2&rhs){
		return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vec2 operator*(float scale, const Vec2 &vec){
		return Vec2(scale * vec.x, scale * vec.y);
	}

	inline Vec2 operator*(const Vec2 &vec, float scale){
		return Vec2(vec.x * scale, vec.y * scale);
	}

}
