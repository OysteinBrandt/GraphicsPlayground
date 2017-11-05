#pragma once

#include <Entities/Component.h>

namespace input { class KeyInput; }
namespace engine::render { class Camera; }

class CameraController : public entities::Component
{
	const input::KeyInput *m_input;
	engine::render::Camera *m_camera;

public:
	CameraController(const input::KeyInput &keyInput, engine::render::Camera &camera);

	void update(float dt) override;
};