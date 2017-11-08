#pragma once

#include "KeyMapper.h"
#include "Input/KeyInput.h"
#include "Scenes/SimpleGame.h"

#include <memory>
#include <chrono>

namespace engine::render { class Renderable; }

class Editor
{
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;
	input::KeyMapper m_keyMapper;
	input::KeyInput m_keyInput;
	std::unique_ptr<scenes::SimpleGame> m_gameScene;
	int frames;

public:
	Editor();

	void update();
	void render(float width, float height);

};

