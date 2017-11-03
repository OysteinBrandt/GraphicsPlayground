#pragma once

#include <Rendering/Renderer.h>
#include <Rendering/Shader.h>
#include <Entities/Entity.h>
#include <Entities/Components/RendererComponent.h>
#include <Entities/Components/PhysicsComponent.h>
#include <Entities/Components/Boundary.h>
#include <Entities/Components/LerpComponent.h>
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
	entities::Entity m_lerper;
	
	std::vector<math::Vec3> m_shipVerices;
	std::vector<GLushort> m_shipIndices;
	std::vector<math::Vec3> m_boundaryVertices;
	std::vector<GLushort> m_boundaryIndices;
	std::vector<math::Vec3> m_lerpPoints;

	entities::component::PhysicsComponent m_shipPhysics;
	entities::component::Boundary m_shipBoundaryHandler;
	engine::render::Renderer m_renderer;
	engine::render::Shader m_shader;
	engine::render::Renderable *m_shipRenderable;
	engine::render::Renderable *m_lerpRenderable;
	entities::component::RendererComponent m_shipRenderer;
	entities::component::RendererComponent m_lerpRenderer;
	entities::component::LerpComponent m_lerpLerper;

	input::KeyInput m_keyInput;
	ControllerComponent m_shipController;
public:
	Editor();

	void update();
	void render(float width, float height);

private:

	void addShips();
	void addLerper(engine::render::Geometry *geometry);
	void addBoundaries();
};

