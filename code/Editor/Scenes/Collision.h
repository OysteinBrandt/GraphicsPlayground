#pragma once

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Positional.h>
#include <memory>

namespace engine::render { class Renderer; }
namespace engine::render { class OpenGLModel; }

struct Sphere
{
	Sphere() : entity(std::make_unique<entities::Entity>()), translator(std::make_unique<entities::component::Positional>())
	{}

	std::unique_ptr<entities::Entity> entity;
	std::unique_ptr<entities::component::Positional> translator;
};

namespace scenes
{
	class Collision
	{
		std::vector<Sphere> m_spheres;

	public:
		Collision(engine::render::Renderer &renderer);
		void update(float dt);

	private:

		void addSphere(engine::render::Renderer& renderer, const engine::render::OpenGLModel& model, const math::Vec3& pos);
	};
}