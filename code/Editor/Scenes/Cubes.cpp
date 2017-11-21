#include "Cubes.hpp"
#include "Shapes/Cube.h"
#include <Rendering/Renderer.h>
#include <Rendering/OpenGLModel.h>

namespace scenes
{

	Cubes::Cubes(engine::render::Renderer &renderer)
	{
		shapes::Cube cube{ 1.0f };
		auto model = renderer.addGeometry(cube.vertices, cube.indices, cube.colors, GL_TRIANGLES);

		//renderer.getModel(model)->renderOutline(true);
		auto instance = renderer.addRenderable(model);
		m_cube1Transform.assign(&renderer, instance);
		m_cube1.addComponent(&m_cube1Transform);
		m_cube1.position = { -1.f, 0.f, 0.f };

		auto instance2 = renderer.addRenderable(model);
		m_cube2Transform.assign(&renderer, instance2);
		m_cube2.addComponent(&m_cube2Transform);
		m_cube2.position = { 1.f, 0.f, 0.f };
	}

	void Cubes::update(float dt)
	{
		m_cube1.position -= math::Vec3{ 0.05f, 0.f, 0.f } * dt;
		m_cube1.update(dt);
		m_cube2.position += math::Vec3{ 0.05f, 0.f, 0.f } * dt;
		m_cube2.update(dt);
	}

}