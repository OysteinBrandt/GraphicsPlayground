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
#define FPS_CAMERA

      //MousePosition centerSceen{ m_window.size.startX + m_window.size.width / 2, m_window.size.startY + m_window.size.height / 2 };
      const Point deltaMousePos{ mouse.x - m_oldMousePos.x, mouse.y - m_oldMousePos.y };
      if (sqrt(deltaMousePos.x * deltaMousePos.x + deltaMousePos.y * deltaMousePos.y) > 5.0)
      {
        //SetCursorPos(centerSceen.x, centerSceen.y);
        m_oldMousePos = /*centerSceen;*/{ mouse.x, mouse.y };
        return;
      }
#ifdef FPS_CAMERA
      //SetCursorPos(centerSceen.x, centerSceen.y);

      const float speed{ 10.0f * dt };
      m_camera->rotate(-deltaMousePos.x * speed, m_camera->up());

      const auto rightDir = math::cross(m_camera->direction(), m_camera->up());
      m_camera->rotate(-deltaMousePos.y * speed, rightDir);

      m_oldMousePos = /*centerSceen;*/{ mouse.x, mouse.y };
#else // orbit
      m_camera->rotate(-delta.x * cameraMouseSpeed, m_camera->up());
      const auto rightDir = math::cross(m_camera->direction(), m_camera->up());
      m_camera->rotate(-delta.y * cameraMouseSpeed, rightDir);

#endif
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
    const auto direction = math::cross(m_camera->direction(), m_camera->up())  * (-1.f);
    m_camera->translate(direction * speed);
  }
  if (keyboard.S.isDown)
  {
    m_camera->translate(m_camera->direction() * (-speed));
  }
  if (keyboard.D.isDown)
  {
    const auto direction = math::cross(m_camera->direction(), m_camera->up());
    m_camera->translate(direction * speed);
  }
}
