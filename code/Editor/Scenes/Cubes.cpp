#include "Cubes.hpp"
#include "Shapes/Cube.h"
#include <Rendering/Renderer.h>
#include <Rendering/OpenGLModel.h>

static float incPos{ 0.f };

namespace scenes
{

	Cubes::Cubes(engine::render::Renderer &renderer)
	{
		shapes::Cube cube{ 1.0f };
		auto model = renderer.addGeometry(cube.vertices, cube.indices, cube.colors, GL_TRIANGLES);

		m_cubes.reserve(100);
		for (int i = 0; i < 50; ++i)
			addCube(renderer, model);
	}

	void Cubes::update(float dt)
	{
		for (auto &cube : m_cubes)
			cube.entity.update(dt);

		for (int i = 0; i < 50; ++i)
		{
			if (i % 2 == 0)
				m_cubes.at(i).entity.orientation += 0.5f * dt;
		}
		//m_cube1.position -= math::Vec3{ 0.05f, 0.f, 0.f } * dt;
		//m_cube1.update(dt);
		//m_cube2.position += math::Vec3{ 0.05f, 0.f, 0.f } * dt;
		//m_cube2.update(dt);
	}

	void Cubes::addCube(engine::render::Renderer &renderer, size_t model)
	{
		auto &cube = m_cubes.emplace_back(CubeData{});
		auto instance = renderer.addRenderable(model);
		cube.pos.assign(&renderer, instance);
		cube.entity.addComponent(&cube.pos);	// * Component becomes invalid when reallocation happens
		cube.entity.position = { incPos, incPos, incPos };
		incPos++;
	}

}