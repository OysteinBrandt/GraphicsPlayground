#pragma once

#include "Math/Mat4.h"
#include "DllHelper.h"
#include "Math/Constants.h"
#include "Assert/AssertException.h"

namespace engine::render
{
	class Camera
	{
		math::Mat4 m_viewMatrix;
		math::Mat4 m_projectionMatrix;

		math::Vec3 m_position;
		math::Vec3 m_direction;
		math::Vec3 m_up;
		float m_fov{ math::PI/2 };
		float m_nearPlane = 1.f;
		float m_farPlane = 10.0f;

	public:

		Camera()
		{ }

		Camera(const math::Vec3 &position) : m_position(position), m_direction{0.f, 0.f, 1.f}, m_up{0.f, 1.f, 0.f}
		{ }

		const math::Vec3& direction() const
		{
			return m_direction;
		}

		const math::Vec3& up() const
		{
			return m_up;
		}

		void update()
		{
			m_viewMatrix = lookAt(m_position, m_position + m_direction, m_up);
		}

		OBR_API void updateProjection(float width, float height);

		math::Mat4 viewMatrix() const
		{
			return m_viewMatrix;
		}

		math::Mat4 projectionMatrix() const
		{
			return m_projectionMatrix;
		}

		void rotate(float radians, const math::Vec3 &axis)
		{
			m_direction = math::Mat4::rotate(radians, axis) * m_direction;
		}

		void translate(const math::Vec3 &position)
		{
			m_position += position;
		}

	private:

		OBR_API math::Mat4 lookAt(const math::Vec3 &pos, const math::Vec3 &target, const math::Vec3 &up);

	};
}