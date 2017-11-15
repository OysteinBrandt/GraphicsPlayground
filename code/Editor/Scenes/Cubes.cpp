#include "Cubes.hpp"
#include "Shapes/Cube.h"
#include <Rendering/Renderer.h>
#include <Rendering/OpenGLModel.h>

namespace scenes
{

	Cubes::Cubes(engine::render::Renderer &renderer)
	{
		m_cube.addComponent(&m_physics);

		shapes::Cube cube{ 1.0f };
		auto model = renderer.addGeometry(cube.vertices, cube.indices, GL_TRIANGLES);
		renderer.getModel(model)->renderOutline(true);
		auto instance = renderer.addRenderable(model);
		m_cube1Transform.assign(renderer.getRenderable(instance));
		m_cube.addComponent(&m_cube1Transform);

		auto instance2 = renderer.addRenderable(model);
		m_cube2Transform.assign(renderer.getRenderable(instance2));
		m_cube.addComponent(&m_cube2Transform);
		m_cube2Transform.position({2.f, 0.f, 0.f});	// TODO: Fix assigning position for each renderable
	}

	void Cubes::update(float dt)
	{
		m_cube.update(dt);
	}

}