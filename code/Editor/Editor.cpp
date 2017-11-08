#include "Editor.h"
#include "MenuChoise.h"
#include <iostream>

Editor::Editor() : m_keyInput(m_keyMapper, input::MenuChoise::MAX)
{
	GLenum errorCode = glewInit();
	if (errorCode != 0)
		std::cout << "Failed to initialize glew!" << std::endl;

	m_gameScene = std::make_unique<scenes::SimpleGame>(m_keyInput);
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
		std::cout << (1 / dt) << std::endl;
		frames = 0;
	}

	m_keyInput.update();
	m_gameScene->update(dt);
}

void Editor::render(float width, float height)
{
	// TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
	m_gameScene->render(width, height);
}