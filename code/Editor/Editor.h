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
	
	entities::Entity m_ship;
	
	std::vector<math::Vec3> m_shipVerices;
	std::vector<GLushort> m_shipIndices;
	std::vector<math::Vec3> m_boundaryVertices;
	std::vector<GLushort> m_boundaryIndices;

	entities::component::PhysicsComponent m_shipPhysics;
	engine::render::Renderer m_renderer;
	engine::render::Renderable* m_shipRenderable;
	entities::component::RendererComponent m_shipRenderer;

	input::KeyInput m_keyInput;
	ControllerComponent m_shipController;
public:
	Editor();

	void update();
	void render(float width, float height);

private:

	void addShip();
	void addBoundaries();
};

