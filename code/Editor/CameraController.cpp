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
      const Point deltaMousePos{ mouse.x - m_oldMousePos.x, mouse.y - m_oldMousePos.y };
      if (sqrt(deltaMousePos.x * deltaMousePos.x + deltaMousePos.y * deltaMousePos.y) > 5.0)
      {
        m_oldMousePos = { mouse.x, mouse.y };
        return;
      }

      // TODO: Hide mouse on LB pressed and keep it at it's location

      // TODO: Limit pitch to be between 89 and -89 degrees

      const float speed{ 10.0f * dt };
      m_camera->rotate(-deltaMousePos.x * speed, math::Mat4::Axis::Y);  // static up vector works when we do not roll
      
      // TODO: Ensure same pitch and yaw when mouse distance traveled is equal

      const auto rightDir = math::cross(m_camera->direction(), m_camera->up().normalized());
      m_camera->rotate(-deltaMousePos.y * speed, rightDir);

      m_oldMousePos = { mouse.x, mouse.y };
    }
  }

  const auto& keyboard = m_application.input.keyboard;
  const auto speed{ 5.0f * dt };
  if (keyboard.W.isDown)
  {
    m_camera->translate(m_camera->direction() * speed);
  }
  if (keyboard.A.isDown)
  {
    const auto left = math::cross(m_camera->direction(), m_camera->up()).normalized()  * (-1.f);
    m_camera->translate(left * speed);
  }
  if (keyboard.S.isDown)
  {
    m_camera->translate(m_camera->direction() * (-speed));
  }
  if (keyboard.D.isDown)
  {
    const auto right = math::cross(m_camera->direction(), m_camera->up().normalized());
    m_camera->translate(right * speed);
  }
}
