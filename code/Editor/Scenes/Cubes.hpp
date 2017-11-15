#pragma once

#include <Entities/Entity.h>
#include <Entities/Components/Positional.h>
#include <Entities/Components/Physics.h>
#include <Rendering/Renderable.h>

namespace engine::render { class Renderer; }

namespace scenes
{
	class Cubes
	{
		entities::Entity m_cube;
		entities::component::Physics m_physics;
		entities::component::Positional m_cube1Transform;
		entities::component::Positional m_cube2Transform;

	public:

		Cubes(engine::render::Renderer &renderer);

		void update(float dt);
	};
}