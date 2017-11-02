#include "ControllerComponent.h"

#include <Entities/Entity.h>
#include <Entities/Components/PhysicsComponent.h>
#include <Input/KeyInput.h>
#include "MenuChoise.h"
#include <Math/Vec3.h>

using entities::component::PhysicsComponent;

ControllerComponent::ControllerComponent(const input::KeyInput & keyInput, entities::component::PhysicsComponent& physics)
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
