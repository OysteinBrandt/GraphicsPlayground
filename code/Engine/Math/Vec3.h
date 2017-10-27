#pragma once
#include <math.h>
#include <cassert> // TODO: Replace

namespace math {

	class Vec3
	{
	public:

		float x;
		float y;
		float z;

		Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
		{}

		//-----------------------------------------------

		inline void operator+=(const Vec3 &other) {
			x += other.x;
			y += other.y;
			z += other.z;
		}

		inline void operator-=(const Vec3 &other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		inline void operator*=(float scale) {
			x *= scale;
			y *= scale;
			z *= scale;
		}

		inline Vec3 perpCW() const {
			return Vec3(y, -x, 0);
		}

		inline Vec3 perpCCW() const {
			return Vec3(-y, x, 0);
		}

		inline float dot(const Vec3 &vec) const {
			return (x * vec.x) + (y * vec.y) + (z * vec.z);
		}

		inline float length() const {
			return sqrtf(lengthSquared());
		}

		inline float lengthSquared() const {
			return this->dot(*this);
		}

		inline Vec3 normalized() const;

		inline Vec3 projectOnto(const Vec3 &target) const;
	};

	/***********************************************************/

	inline Vec3 operator+(const Vec3 &lhs, const Vec3&rhs) {
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	inline Vec3 operator-(const Vec3 &lhs, const Vec3&rhs) {
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	inline Vec3 operator*(float scale, const Vec3 &vec) {
		return Vec3(scale * vec.x, scale * vec.y, scale * vec.z);
	}

	inline Vec3 operator*(const Vec3 &vec, float scale) {
		return Vec3(vec.x * scale, vec.y * scale, vec.z * scale);
	}

	inline Vec3 operator/(const Vec3 &vec, float scale) {
		return Vec3(vec.x/scale, vec.y/scale, vec.z/scale);
	}

	inline Vec3 operator/(float scale, const Vec3 &vec) {
		return Vec3(scale/vec.x, scale/vec.y, scale/vec.z);
	}

	inline Vec3 Vec3::normalized() const {
		const float magnitude = length();
		const bool isValidLength = isnormal(magnitude);
		assert(isValidLength);
		if (!isValidLength)
			return Vec3{};

		const float inversLength = 1.0f / magnitude;
		return inversLength * (*this);
	}

	inline Vec3 Vec3::projectOnto(const Vec3 &target) const {
		return (this->dot(target) / target.lengthSquared()) * target;
	}

	inline Vec3 lerp(float alpha, const Vec3 &first, const Vec3 &second) {
		return (1.0f - alpha) * first + alpha * second;
	}

}
