#pragma once

#include <Rendering/Renderer.h>
#include <Entities/Entity.h>
#include <Entities/Components/RendererComponent.h>
#include <Entities/Components/PhysicsComponent.h>
#include "ControllerComponent.h"
#include "KeyMapper.h"
#include "Input/KeyInput.h"
#include <chrono>

namespace engine::render { class Renderable; }

class Editor
{
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;
	input::KeyMapper m_keyMapper;
	input::KeyInput m_keyInput;
	
	entities::Entity m_ship;
	std::vector<math::Vec3> shipVerices;
	std::vector<GLushort> shipIndices;

	entities::Entity m_boundaries;
	std::vector<math::Vec3> boundaries;
	std::vector<GLushort> boundIndices;

	entities::component::RendererComponent m_shipRenderer;
	entities::component::PhysicsComponent m_shipPhysics;
	ControllerComponent m_shipController;

	engine::render::Renderer m_renderer;
	engine::render::Renderable* m_shipRenderable;
	engine::render::Renderable* m_lerpRenderable;

public:
	Editor();

	void update();
	void render(float width, float height);

private:

	void addShip();
	void addBoundaries();
};

