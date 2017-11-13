#include "Editor.h"
#include "MenuChoise.h"
#include <iostream>

Editor::Editor(const engine::render::WindowSize<int> &windowSize) 
	: m_keyInput(m_keyMapper, input::MenuChoise::MAX)
{
	GLenum errorCode = glewInit();
	if (errorCode != 0)
		std::cout << "Failed to initialize glew!" << std::endl;

	m_camera = engine::render::Camera{{ 0.f, 3.f, -3.f }};
	m_cameraController = std::make_unique<CameraController>(m_keyInput, m_camera, windowSize);
	m_shader = std::make_unique<engine::render::Shader>("defaultVertex.vert", "defaulFragment.frag");

	m_renderer = std::make_unique<engine::render::Renderer>(m_camera, *m_shader);
	//m_gameScene = std::make_unique<scenes::SimpleGame>(m_keyInput);
	m_cubeScene = std::make_unique<scenes::Cubes>(*m_renderer);
	frames = 0;
}

void Editor::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> deltaTime = now - m_frameTimer;
	m_frameTimer = now;
	const auto dt = deltaTime.count();

	++frames;
	if (frames % 100 == 0)
	{
		//std::cout << (1 / dt) << std::endl;
		frames = 0;
	}

	m_cameraController->update(dt);
	m_keyInput.update();
	m_camera.update();
	m_cubeScene->update(dt);
	//m_gameScene->update(dt);
}

void Editor::render(float width, float height)
{
	// TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
	m_camera.updateProjection(width, height);
	m_renderer->render(width, height);
	//m_gameScene->render(width, height);
}