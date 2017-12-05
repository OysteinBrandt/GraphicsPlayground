#pragma once

#include <Entities/Component.h>

namespace input { class KeyInput; }

class ShapeController : public entities::Component
{
	const input::KeyInput *m_input;

public:

	ShapeController(const input::KeyInput &keyInput);
	void update(float) override;
};