#pragma once

#include "Math/Mat4.h"
#include "DllHelper.h"
#include "Math/Constants.h"

namespace engine::render
{
	class Camera
	{
		math::Mat4 m_viewMatrix;
		math::Mat4 m_projectionMatrix;

		math::Vec3 m_position;
		float m_fov{ math::PI/2 };
		float m_nearPlane = 1.f;
		float m_farPlane = 10.0f;

	public:
		math::Vec3 direction;
		math::Vec3 up;

		Camera()
		{ }

		Camera(const math::Vec3 &position) : m_position(position), direction{0.f, 0.f, 1.f}, up{0.f, 1.f, 0.f}
		{ }

		void update()
		{
			m_viewMatrix = math::Mat4::rotate(direction.x, math::Mat4::Axis::Y) * 
				math::Mat4::rotate(direction.y, math::Mat4::Axis::X) *
				math::Mat4::translate(m_position);
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

		void translate(const math::Vec3 &position)
		{
			m_position += position;
		}

	};
}