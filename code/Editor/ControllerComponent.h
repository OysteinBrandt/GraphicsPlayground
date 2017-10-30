#pragma once

#include <Entities/Component.h>

namespace input { class KeyInput; }
namespace entities::component { class PhysicsComponent; }

class ControllerComponent : public entities::Component
{
	const input::KeyInput *m_input;
	entities::component::PhysicsComponent *m_physics;

public:
	ControllerComponent(const input::KeyInput &keyInput, entities::component::PhysicsComponent& physics);

	void update(float) override;
};