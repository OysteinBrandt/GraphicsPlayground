#pragma once

#include "Engine/Math/Mat4.h"
#include "Engine/DllHelper.h"
#include "Engine/Math/Constants.h"
#include "Engine/Assert/AssertException.h"

namespace engine::render
{
  class Camera
  {
    math::Mat4 m_viewMatrix;
    math::Mat4 m_projectionMatrix;

    math::Vec3 m_position;
    math::Vec3 m_direction;
    math::Vec3 m_up;
    float m_fov;
    float m_nearPlane;
    float m_farPlane;

  public:

    Camera()
    { }

    Camera(const math::Vec3 &position, const math::Vec3 &target = { 0.f, 0.f, 0.f })
      : m_position(position), m_direction{ 0.f, 0.f, 1.f }, m_up{ 0.f, 1.f, 0.f },
      m_fov{ math::PI / 2 }, m_nearPlane{ 0.1f }, m_farPlane{ 100.f }
    {
      lookAt(target);
    }

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

    ENGINE_API void updateProjection(float width, float height);

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
      const auto rotation = math::Mat4::rotate(radians, axis);
      m_direction = rotation * m_direction;
      m_up = rotation * m_up;
    }

    void translate(const math::Vec3 &position)
    {
      m_position += position;
    }

    void lookAt(const math::Vec3 &target)
    {
      const auto direction = target - m_position;
      m_direction = direction.normalized();
      const auto rightDir = math::cross(m_up, m_direction);
      m_up = math::cross(m_direction, rightDir);
    }

  private:

    ENGINE_API math::Mat4 lookAt(const math::Vec3 &pos, const math::Vec3 &target, const math::Vec3 &up);

  };
}