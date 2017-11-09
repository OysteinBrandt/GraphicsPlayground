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
		auto *model = renderer.addGeometry(cube.vertices, cube.indices, GL_TRIANGLES);
		model->renderOutline(true);
		m_renderable = renderer.addRenderable(model);
		m_pos.assign(m_renderable);
		m_cube.addComponent(&m_pos);
	}

	void Cubes::update(float dt)
	{
		m_cube.update(dt);
	}

}