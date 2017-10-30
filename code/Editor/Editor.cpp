#include "Editor.h"
#include <Math/Mat3.h>
#include "MenuChoise.h"

using engine::render::Geometry;

Editor::Editor() : m_keyInput(m_keyMapper, input::MenuChoise::MAX), m_shipController(m_keyInput, m_shipPhysics)
{
	shipVerices =
	{
		math::Vec3(+0.0f, +0.14142135623f, 1),
		//math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(-0.1f, -0.1f, 1),
		//math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(+0.1f, -0.1f, 1)
		//math::Vec3(+1.0f, +0.0f, 0.0f)
	};

	shipIndices = { 0, 1, 2 };

	//boundaries =
	//{
	//	math::Vec3{ 0.f, 1.f, 1.f },
	//	math::Vec3{ -1.f, 0.f, 1.f },
	//	math::Vec3{ 0.f, -1.f, 1.f },
	//	math::Vec3{ 1.f, 0.f, 1.f },
	//};

	//boundIndices = { 0, 1, 1, 2, 2, 3, 3, 0 };

	m_ship.addComponent(&m_shipController);
	m_ship.addComponent(&m_shipPhysics);

	const Geometry &shipGeometry = m_renderer.addGeometry(shipVerices, shipIndices, GL_TRIANGLES);
	m_shipRenderable = &m_renderer.addRenderable(shipGeometry);
	m_shipRenderer.assign(m_shipRenderable);
	m_ship.addComponent(&m_shipRenderer);
	//m_lerpRenderable = m_renderer.addRenderable(shipGeometry);
}

void Editor::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> deltaTime = now - m_frameTimer;
	m_frameTimer = now;

	m_keyInput.update();
	m_ship.update(deltaTime.count());
}

void Editor::render()
{
	m_renderer.render();
}