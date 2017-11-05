#include "CameraController.h"

#include <Input/KeyInput.h>
#include <Rendering/Camera.h>
#include "MenuChoise.h"
#include <Math/Vec3.h>
#include <Math/Constants.h>

using engine::render::Camera;

CameraController::CameraController(const input::KeyInput & keyInput, Camera& camera)
{
	m_camera = &camera;
	m_input = &keyInput;
}

void CameraController::update(float dt)
{
	const float cameraSpeed{ 0.5f * dt };

	if (m_input->isActionsHot(input::MenuChoise::CameraRight))
	{
		const auto rightDir = math::cross(m_camera->direction, m_camera->up) * (-1.f);
		m_camera->translate(rightDir * cameraSpeed);
	}
	if (m_input->isActionsHot(input::MenuChoise::CameraLeft))
	{
		const auto leftDir = math::cross(m_camera->direction, m_camera->up);
		m_camera->translate(leftDir * cameraSpeed);
	}
	if (m_input->isActionsHot(input::MenuChoise::CameraForward))
	{
		m_camera->translate(m_camera->direction * (-cameraSpeed));
	}

	if (m_input->isActionsHot(input::MenuChoise::CameraBackward))
	{
		m_camera->translate(m_camera->direction * cameraSpeed);
	}
}
