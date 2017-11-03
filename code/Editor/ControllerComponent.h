#pragma once

#include <Entities/Component.h>

namespace input { class KeyInput; }
namespace entities::component { class Physics; }

class ControllerComponent : public entities::Component
{
	const input::KeyInput *m_input;
	entities::component::Physics *m_physics;

public:
	ControllerComponent(const input::KeyInput &keyInput, entities::component::Physics& physics);

	void update(float) override;
};