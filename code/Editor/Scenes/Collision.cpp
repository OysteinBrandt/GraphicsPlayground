#include "Collision.h"

#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/OpenGLModel.h>
#include <Engine/Generator/Sphere.h>

namespace scenes
{
	Collision::Collision(engine::render::Renderer & renderer)
	{
		const int numSpheres{ 50 };
		m_spheres.reserve(numSpheres);	// TODO: !! This is a workaround, see comment in addSphere(...)
		auto geometry = engine::generator::Sphere(1.f).generate(10, 10);
		auto sphereModel = renderer.add(geometry, GL_TRIANGLES);
		for (int i = 0; i < numSpheres; ++i)
			addSphere(renderer, *sphereModel, {static_cast<float>(i), 0.f, 0.f});
	}

	void Collision::update(float dt)
	{
		for (auto &sphere : m_spheres)
			sphere.entity.update(dt);
	}

	void Collision::addSphere(engine::render::Renderer& renderer, const engine::render::OpenGLModel& model, const math::Vec3& pos)
	{
		auto &sphere = m_spheres.emplace_back(Sphere{});
		auto renderable = renderer.addRenderable(model);
		sphere.translator->assign(renderable.get());
		sphere.entity.addComponent(sphere.translator.get());	// TODO: Parent of Component becomes invalid when reallocation happens (workaround; reserve on m_spheres)
		sphere.entity.position = pos;
	}

}