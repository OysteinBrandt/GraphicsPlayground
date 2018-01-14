#include "ControllerComponent.h"

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Physics.h>
#include <Engine/Input/KeyInput.h>
#include <Engine/Math/Vec3.h>
#include "MenuChoise.h"

using entities::component::Physics;

ControllerComponent::ControllerComponent(const input::KeyInput & keyInput, entities::component::Physics& physics)
{
	m_physics = &physics;
	m_input = &keyInput;
}

void ControllerComponent::update(float)
{
	const float angularVelocity{ 0.001f };
	if (m_input->isActionsHot(input::MenuChoise::RotateLeft))
		m_physics->angularVelocity = angularVelocity;
	else if (m_input->isActionsHot(input::MenuChoise::RotateRight))
		m_physics->angularVelocity = -angularVelocity;
	else
		m_physics->angularVelocity = 0.0f;
	if (m_input->isActionsHot(input::MenuChoise::Accelerate))
	{
		const auto orientation = getParent()->orientation;
		//auto directionToAccel = math::Mat3::rotate(orientation, math::Mat3::Axis::) * frontDirectionOfEntity;
		m_physics->acceleration = math::Vec3{ -sinf(orientation), cosf(orientation) };
	}
}
