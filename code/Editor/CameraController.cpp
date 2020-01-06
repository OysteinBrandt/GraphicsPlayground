#include "CameraController.h"

#include "ApplicationParam.h"
#include <Engine/Render/Camera.h>
#include <Engine/Math/Vec3.h>
#include <Engine/Math/Vec2.h>
#include <Engine/Math/Constants.h>

CameraController::CameraController(engine::render::Camera* const camera, const ApplicationParam& appParam)
  : m_camera(camera), m_application(appParam)
{ }

void CameraController::update(float dt)
{
  const auto& window = m_application.window;
  if (!window.hasFocus)
    return;

  const auto &mouse = m_application.input.mouse;
  if (mouse.leftButtonDown)
  {
    if (mouse.isInside(window))
    {
      const float sensitivity{ 50.0f * dt };
      m_yaw += math::Degrees(mouse.delta_x * sensitivity);
      m_pitch += math::Degrees(-mouse.delta_y * sensitivity);

      m_pitch = std::clamp(m_pitch, -89.0_degrees, 89.0_degrees);

      const math::Vec3 front(
        std::cos(math::to_radians(m_pitch).get()) * std::cos(math::to_radians(m_yaw).get()),
        std::sin(math::to_radians(m_pitch).get()),
        std::cos(math::to_radians(m_pitch).get()) * std::sin(math::to_radians(m_yaw).get())
      );
      m_camera->setDirection(front.normalized());
    }
  }

  if (mouse.delta_scroll != 0)
  {
    //TODO: Scroll speed should dynamic. Perhaps use the largest bounding box in view to scale speed?
    const auto scroll_speed{ 300.0f * dt };
    m_camera->translate(m_camera->direction() * mouse.delta_scroll * scroll_speed);
  }

  const auto& keyboard = m_application.input.keyboard;
  const auto speed{ 2.0f * dt };
  if (keyboard.W.isDown)
  {
    m_camera->translate(m_camera->direction() * speed);
  }
  if (keyboard.A.isDown)
  {
    const auto left = math::cross(m_camera->direction(), {0.f, 1.f, 0.f}).normalized()  * (-1.f);
    m_camera->translate(left * speed);
  }
  if (keyboard.S.isDown)
  {
    m_camera->translate(m_camera->direction() * (-speed));
  }
  if (keyboard.D.isDown)
  {
    const auto right = math::cross(m_camera->direction(), { 0.f, 1.f, 0.f }).normalized();
    m_camera->translate(right * speed);
  }
}
