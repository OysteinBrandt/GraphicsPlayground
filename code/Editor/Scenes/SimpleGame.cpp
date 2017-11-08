#include "SimpleGame.h"
#include <Math/Mat3.h>
#include "../MenuChoise.h"
#include "../KeyMapper.h"
#include "Input/KeyInput.h"

using engine::render::OpenGLModel;

namespace scenes
{

	SimpleGame::SimpleGame(const input::KeyInput &keyInput) :
		m_camera(math::Vec3{ 0.f, 0.f, -3.f }),
		m_cameraController(keyInput, m_camera),
		m_shipController(keyInput, m_shipPhysics),
		m_shipBoundaryHandler(m_shipPhysics, m_boundaryVertices),
		m_lerpLerper(m_lerpPoints, m_shipPhysics),
		m_shader("defaultVertex.vert", "defaulFragment.frag"),
		m_renderer(m_camera, m_shader)
	{
		addShips();
		addBoundaries();
	}

	void SimpleGame::update(float dt)
	{
		m_cameraController.update(dt);
		m_camera.update();
		m_ship.update(dt);
		m_lerper.update(dt);
	}

	void SimpleGame::render(float width, float height)
	{
		// TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
		m_camera.updateProjection(width, height);
		m_renderer.render(width, height);
	}

	void SimpleGame::addShips()
	{
		const std::vector<math::Vec3> shipVerices
		{
			math::Vec3(+0.0f, +0.14142135623f, 1),
			math::Vec3(-0.1f, -0.1f, 1),
			math::Vec3(+0.1f, -0.1f, 1)
		};

		const std::vector<GLushort> shipIndices{ 0, 1, 2 };

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

	void SimpleGame::addBoundaries()
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

	void SimpleGame::addLerper(engine::render::OpenGLModel *model)
	{
		m_lerpPoints =
		{
			math::Vec3{ 0.5f, 0.5f, 0.0f },
			math::Vec3{ -0.5f, 0.5f, 0.0f },
			math::Vec3{ -0.5f, -0.5f, 0.0f },
			math::Vec3{ 0.5f, -0.5f, 0.0f }
		};

		m_lerper.addComponent(&m_lerpLerper);
		m_lerpRenderable = m_renderer.addRenderable(model);
		m_lerpTransform.assign(m_lerpRenderable);
		m_lerper.addComponent(&m_lerpTransform);
	}

}