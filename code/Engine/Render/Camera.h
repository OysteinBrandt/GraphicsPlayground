#pragma once

#include "Engine/Math/Mat4.h"
#include "Engine/DllHelper.h"
#include "Engine/Math/Constants.h"
#include "Engine/Math/Trigonometric.h"
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
    math::Radians m_fov{ 0.f };
    float m_nearPlane{ 0.f };
    float m_farPlane{ 0.f };

  public:

    Camera() = default;

    ENGINE_API Camera(const math::Vec3 &position, const math::Vec3 &target = {});

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

    void rotate(const math::Degrees& deg, const math::Vec3 &axis)
    {
      rotate(math::to_radians(deg), axis);
    }

    void rotate(const math::Radians& rad, const math::Vec3 &axis)
    {
      const auto rotation = math::Mat4::rotate(rad.get(), axis);
      m_direction = rotation * m_direction;
      m_up = rotation * m_up;
    }

    void rotate(const math::Degrees& deg, math::Mat4::Axis axis)
    {
      rotate(math::to_radians(deg), axis);
    }

    void rotate(const math::Radians rad, math::Mat4::Axis axis)
    {
      const auto rotation = math::Mat4::rotate(rad.get(), axis);
      m_direction = rotation * m_direction;
      m_up = rotation * m_up;
    }

    void translate(const math::Vec3 &translation)
    {
      m_position += translation;
    }

    void setPosition(const math::Vec3& position)
    {
      m_position = position;
    }

    void setDirection(const math::Vec3& dir)
    {
      m_direction = dir;
    }

  private:

    ENGINE_API math::Mat4 lookAt(const math::Vec3 &pos, const math::Vec3 &target, const math::Vec3 &up);

  };
}