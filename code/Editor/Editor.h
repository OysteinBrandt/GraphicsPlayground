#pragma once

#include "KeyMapper.h"
#include <Engine/Input/KeyInput.h>
#include "CameraController.h"
#include "Scenes/SimpleGame.h"
#include "Scenes/Cubes.hpp"
#include "Scenes/Collision.h"
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Camera.h>
#include <Engine/Rendering/WindowSize.h>

#include <memory>
#include <chrono>

class Editor
{
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;
	input::KeyMapper m_keyMapper;
	input::KeyInput m_keyInput;
	std::unique_ptr<CameraController> m_cameraController;

	engine::render::Camera m_camera;

	std::unique_ptr<engine::render::Renderer> m_renderer;
	//std::unique_ptr<scenes::SimpleGame> m_gameScene;
	//std::unique_ptr<scenes::Cubes> m_cubeScene;
	std::unique_ptr<scenes::Collision> m_collisionScene;
	int frames;

public:
	Editor(const engine::render::WindowParam &window);

	void update();
	void render(float width, float height);

};

