#pragma once

#include "KeyMapper.h"
#include "Input/KeyInput.h"
#include "CameraController.h"
#include "Scenes/SimpleGame.h"
#include "Scenes/Cubes.hpp"
#include <Rendering/Renderer.h>
#include <Rendering/Camera.h>
#include <Rendering/Shader.h>
#include <Rendering/WindowSize.h>

#include <memory>
#include <chrono>

namespace engine::render { class Renderable; }

class Editor
{
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;
	input::KeyMapper m_keyMapper;
	input::KeyInput m_keyInput;
	std::unique_ptr<CameraController> m_cameraController;

	engine::render::Camera m_camera;
	std::unique_ptr<engine::render::Shader> m_shader;

	std::unique_ptr<engine::render::Renderer> m_renderer;
	//std::unique_ptr<scenes::SimpleGame> m_gameScene;
	std::unique_ptr<scenes::Cubes> m_cubeScene;
	int frames;

public:
	Editor(const engine::render::WindowSize<int> &windowSize);

	void update();
	void render(float width, float height);

};

