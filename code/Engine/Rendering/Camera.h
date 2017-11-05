#pragma once

#include "Math/Mat4.h"

namespace engine::render
{
	class Camera
	{
		math::Mat4 m_matrix;
		math::Vec3 m_position;
		float m_nearPlane;
		float m_farPlane;

	public:
		math::Vec3 direction;
		math::Vec3 up;

		Camera() : direction{0.f, 0.f, -1.f}, up{0.f, 1.f, 0.f}
		{ }

		void update()
		{
			m_matrix = math::Mat4::translate(m_position);
		}

		math::Mat4 viewMatrix() const
		{
			return m_matrix;
		}

		void translate(const math::Vec3 &position)
		{
			m_position += position;
		}

		void rotate(float, math::Mat4::Axis)
		{
		}

	};
}