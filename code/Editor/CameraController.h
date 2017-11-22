#pragma once

#include <Entities/Component.h>
#include <Rendering/WindowSize.h>

namespace input { class KeyInput; }
namespace engine::render { class Camera; }

struct MousePosition
{
	int x;
	int y;
};

class CameraController : public entities::Component
{
	const input::KeyInput *m_input;
	engine::render::Camera *m_camera;
	const engine::render::WindowParam &m_window;
	MousePosition m_oldMousePos{};

public:
	CameraController(const input::KeyInput &keyInput, 
									 engine::render::Camera &camera, 
									 const engine::render::WindowParam &window);

	void update(float dt) override;
};