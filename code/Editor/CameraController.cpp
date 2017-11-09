#include "CameraController.h"

#include <Input/KeyInput.h>
#include <Rendering/Camera.h>
#include "MenuChoise.h"
#include <Math/Vec3.h>
#include <Math/Constants.h>

#include <Windows.h> // TODO: Refactor
#include <string>

using engine::render::Camera;
using namespace input::MenuChoise;

CameraController::CameraController(const input::KeyInput & keyInput, Camera& camera, const engine::render::WindowSize<int> &windowSize)
	: m_windowSize(windowSize)
{
	m_camera = &camera;
	m_input = &keyInput;
}

void CameraController::update(float dt)
{
	const float cameraSpeed{ 1.0f * dt };
	const float cameraMouseSpeed{ 5.0f * dt };
	if (m_input->isActionsHot(MouseLButtonDown))
	{
		// TODO: Camera orbit/rotate
		POINT pos;
		GetCursorPos(&pos);

		// if first click is within view
		if (pos.x > m_windowSize.startX && pos.x < (m_windowSize.startX + m_windowSize.width) &&
			  pos.y > m_windowSize.startY && pos.y < (m_windowSize.startY + m_windowSize.height))
		{
			const MousePosition delta = { pos.x - m_oldMousePos.x, pos.y - m_oldMousePos.y };
			if (sqrt(delta.x * delta.x + delta.y * delta.y) > 5.0)
			{
				m_oldMousePos = { pos.x, pos.y };
				return;
			}

			const auto rightDir = math::cross(m_camera->direction, m_camera->up);
			const auto rotation = math::Mat4::rotate(delta.x * ( cameraMouseSpeed), math::Mat4::Axis::Y) *
														math::Mat4::rotate(delta.y * (-cameraMouseSpeed), math::Mat4::Axis::X);

			m_camera->direction = rotation * m_camera->direction;
			//m_camera->up = math::cross(m_camera->direction, (rotation * rightDir * (-1))).normalized();
			m_oldMousePos = { pos.x, pos.y };
		}
	}
	if (m_input->isActionsHot(CameraRight))
	{
		const auto rightDir = math::cross(m_camera->direction, m_camera->up);
		m_camera->translate(rightDir * cameraSpeed);
	}
	if (m_input->isActionsHot(CameraLeft))
	{
		const auto leftDir = math::cross(m_camera->direction, m_camera->up)  * (-1.f);
		m_camera->translate(leftDir * cameraSpeed);
	}
	if (m_input->isActionsHot(CameraForward))
	{
		m_camera->translate(m_camera->direction * cameraSpeed);
	}

	if (m_input->isActionsHot(CameraBackward))
	{
		m_camera->translate(m_camera->direction * (-cameraSpeed));
	}
}
