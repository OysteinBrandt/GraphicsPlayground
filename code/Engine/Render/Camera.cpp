#include "Camera.h"
#include <cmath>

engine::render::Camera::Camera(const math::Vec3 &position, const math::Vec3 &target)
  : m_position(position), m_direction{ 0.f, 0.f, -1.f }, m_up{ 0.f, 1.f, 0.f },
    m_fov{ math::to_radians(90.0_degrees) }, m_nearPlane{ 0.1f }, m_farPlane{ 100.f }
{
  lookAt(m_position, m_position + m_direction, m_up);
}

void engine::render::Camera::updateProjection(float width, float height)
{
  float aspectRatio = width / height;
  float yScale = (1.f / tanf(m_fov.get() / 2)) * aspectRatio;
  float xScale = yScale / aspectRatio;
  float frustumLength = m_farPlane - m_nearPlane;

  m_projectionMatrix.x[0] = xScale;
  m_projectionMatrix.y[1] = yScale;
  m_projectionMatrix.z[2] = -((m_farPlane + m_nearPlane) / frustumLength);
  m_projectionMatrix.z[3] = -1.f;
  m_projectionMatrix.w[2] = -((2 * m_nearPlane * m_farPlane) / frustumLength);
  m_projectionMatrix.w[3] = 0.f;
}

math::Mat4 engine::render::Camera::lookAt(const math::Vec3 & pos, const math::Vec3 & target, const math::Vec3 & up)
{
  const auto w = (pos - target).normalized();
  const auto u = math::cross(up, w).normalized();
  const auto v = math::cross(w, u).normalized();

  return math::Mat4
  {
    u.x, u.y, u.z, -(u.dot(pos)),
    v.x, v.y, v.z, -(v.dot(pos)),
    w.x, w.y, w.z, -(w.dot(pos)),
    0,   0,   0,             1
  };
}

#if 0 // @@@ Since the cross-product below is not normalized it can create some cool side effects
      // Eg. zoom in from the sky or jump off screen effect
math::Mat4 engine::render::Camera::lookAt(const math::Vec3 & pos, const math::Vec3 & target, const math::Vec3 & up)
{
  const auto w = (pos - target).normalized();
  const auto u = math::cross(up, w);
  const auto v = math::cross(w, u);

  return math::Mat4
  {
    u.x, u.y, u.z, -(u.dot(pos)),
    v.x, v.y, v.z, -(v.dot(pos)),
    w.x, w.y, w.z, -(w.dot(pos)),
      0,   0,   0,             1
  };
}
#endif

#if 0 // TODO: Could be needed in a 2D environment
math::Mat4 engine::render::Camera::aspectCorrectionMatrix(float width, float height) const
{
	float aspectRatio = width / height;

	if (aspectRatio > 1)
		return math::Mat4::scale(1.0f / aspectRatio, 1.0f, 1.f);
	else
		return math::Mat4::scale(1.0f, aspectRatio, 1.f);
}
#endif
