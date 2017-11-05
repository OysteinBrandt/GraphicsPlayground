#include "Editor.h"
#include <Math/Mat3.h>
#include "MenuChoise.h"

using engine::render::OpenGLModel;

Editor::Editor() :
	m_keyInput(m_keyMapper, input::MenuChoise::MAX),
	m_camera(math::Vec3{ 0.f, 0.f, -3.f }),
	m_cameraController(m_keyInput, m_camera),
	m_shipController(m_keyInput, m_shipPhysics), 
	m_shipBoundaryHandler(m_shipPhysics, m_boundaryVertices),
	m_lerpLerper(m_lerpPoints, m_shipPhysics),
	m_shader("defaultVertex.vert", "defaulFragment.frag"),
	m_renderer(m_camera, m_shader)
{
	addShips();
	addBoundaries();
}

void Editor::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> deltaTime = now - m_frameTimer;
	m_frameTimer = now;
	const auto dt = deltaTime.count();

	m_keyInput.update();
	m_cameraController.update(dt);
	m_camera.update();
	m_ship.update(dt);
	m_lerper.update(dt);
}

void Editor::render(float width, float height)
{
	// TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
	m_camera.updateProjection(width, height);
	m_renderer.render(width, height);
}

void Editor::addShips()
{
	const std::vector<math::Vec3> shipVerices =
	{
		math::Vec3(+0.0f, +0.14142135623f, 1),
		//math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(-0.1f, -0.1f, 1),
		//math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(+0.1f, -0.1f, 1)
		//math::Vec3(+1.0f, +0.0f, 0.0f)
	};

	const std::vector<GLushort> shipIndices = { 0, 1, 2 };

	m_ship.addComponent(&m_shipController);
	m_ship.addComponent(&m_shipPhysics);
	m_ship.addComponent(&m_shipBoundaryHandler);

	// TODO: Find a solution to the problem of returning pointer/reference to vector elements, as they will be invalidated when the size increases!!!
	OpenGLModel *shipModel = m_renderer.addGeometry(shipVerices, shipIndices, GL_TRIANGLES);
	m_shipRenderable = m_renderer.addRenderable(shipModel);
	m_shipTransform.assign(m_shipRenderable);
	m_ship.addComponent(&m_shipTransform);
	
	addLerper(shipModel);
}

void Editor::addBoundaries()
{
	m_boundaryVertices =
	{
		math::Vec3{ 0.f, 1.f, 1.f },
		math::Vec3{ -1.f, 0.f, 1.f },
		math::Vec3{ 0.f, -1.f, 1.f },
		math::Vec3{ 1.f, 0.f, 1.f },
	};

	m_boundaryIndices = { 0, 1, 1, 2, 2, 3, 3, 0 };

	OpenGLModel *boundaryModel = m_renderer.addGeometry(m_boundaryVertices, m_boundaryIndices, GL_LINES);
	m_renderer.addRenderable(boundaryModel);
}

void Editor::addLerper(engine::render::OpenGLModel *model)
{
	m_lerpPoints = 
	{
		math::Vec3{  0.5f, 0.5f, 0.0f },
		math::Vec3{ -0.5f, 0.5f, 0.0f },
		math::Vec3{ -0.5f, -0.5f, 0.0f },
		math::Vec3{  0.5f, -0.5f, 0.0f }
	};

	m_lerper.addComponent(&m_lerpLerper);
	m_lerpRenderable = m_renderer.addRenderable(model);
	m_lerpTransform.assign(m_lerpRenderable);
	m_lerper.addComponent(&m_lerpTransform);
}
