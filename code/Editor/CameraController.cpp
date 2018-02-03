#include "CameraController.h"

#include <Engine/Input/KeyInput.h>
#include <Engine/Render/Camera.h>
#include <Engine/Math/Vec3.h>
#include <Engine/Math/Constants.h>
#include "MenuChoise.h"

#include <Windows.h> // TODO: Refactor
#include <iostream> // TODO: For debugging, remove

using engine::render::Camera;
using namespace input::MenuChoise;

CameraController::CameraController(const input::KeyInput & keyInput, Camera& camera, const engine::render::WindowParam &window)
  : m_window(window)
{
  m_camera = &camera;
  m_input = &keyInput;
}

void CameraController::update(float dt)
{
  if (!m_window.hasFocus)
    return;

  const float cameraSpeed{ 5.0f * dt };
  const float cameraMouseSpeed{ 10.0f * dt };
  if (m_input->isActionsHot(MouseLButtonDown))
  {
    POINT pos;
    GetCursorPos(&pos);

    // TODO: Improve
    // Hide mouse after click
    // Keep mouse inside view??
    if (pos.x > m_window.size.startX && pos.x < (m_window.size.startX + m_window.size.width) &&
      pos.y > m_window.size.startY && pos.y < (m_window.size.startY + m_window.size.height))
    {
#define FPS_CAMERA

      MousePosition centerSceen{ m_window.size.startX + m_window.size.width / 2, m_window.size.startY + m_window.size.height / 2 };
      const MousePosition delta = { pos.x - m_oldMousePos.x, pos.y - m_oldMousePos.y };
      if (sqrt(delta.x * delta.x + delta.y * delta.y) > 5.0)
      {
        //SetCursorPos(centerSceen.x, centerSceen.y);
        m_oldMousePos = /*centerSceen;*/{ pos.x, pos.y };
        return;
      }
#ifdef FPS_CAMERA
      //SetCursorPos(centerSceen.x, centerSceen.y);

      //std::cout << "deltaX: " << delta.x << "/tdeltaY: " << delta.y << std::endl;

      m_camera->rotate(-delta.x * cameraMouseSpeed, m_camera->up());

      const auto rightDir = math::cross(m_camera->direction(), m_camera->up());
      m_camera->rotate(-delta.y * cameraMouseSpeed, rightDir);

      m_oldMousePos = /*centerSceen;*/{ pos.x, pos.y };
#else // orbit
      m_camera->rotate(-delta.x * cameraMouseSpeed, m_camera->up());
      const auto rightDir = math::cross(m_camera->direction(), m_camera->up());
      m_camera->rotate(-delta.y * cameraMouseSpeed, rightDir);

#endif
    }
  }
  if (m_input->isActionsHot(CameraRight))	// TODO: Should only work when window has focus
  {
    const auto rightDir = math::cross(m_camera->direction(), m_camera->up());
    m_camera->translate(rightDir * cameraSpeed);
  }
  if (m_input->isActionsHot(CameraLeft))
  {
    const auto leftDir = math::cross(m_camera->direction(), m_camera->up())  * (-1.f);
    m_camera->translate(leftDir * cameraSpeed);
  }
  if (m_input->isActionsHot(CameraForward))
  {
    m_camera->translate(m_camera->direction() * cameraSpeed);
  }

  if (m_input->isActionsHot(CameraBackward))
  {
    m_camera->translate(m_camera->direction() * (-cameraSpeed));
  }
}
