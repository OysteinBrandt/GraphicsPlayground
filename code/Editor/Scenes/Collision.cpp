#include "Collision.h"

#include <Engine/Render/OpenGL/Renderer.h>
#include <Engine/Render/OpenGL/OpenGLModel.h>
#include <Engine/Generator/Sphere.h>

namespace scenes
{
  Collision::Collision(engine::render::opengl::Renderer& renderer)
  {
    const int numSpheres{ 50 };
    auto geometry = engine::generator::Sphere(0.5f).generate(10, 10);
    auto sphereModel = renderer.add(geometry, GL_TRIANGLES);
    for (int i = 0; i < numSpheres; ++i)
      addSphere(renderer, *sphereModel, { static_cast<float>(i), 0.f, 0.f });
  }

  void Collision::update(float dt)
  {
    for (auto &sphere : m_spheres)
      sphere.entity->update(dt);
  }

  void Collision::addSphere(engine::render::opengl::Renderer& renderer, const engine::render::opengl::OpenGLModel& model, const math::Vec3& pos)
  {
    auto &sphere = m_spheres.emplace_back(Sphere{});
    auto renderable = renderer.add(model);
    sphere.entity->position = pos;
    sphere.entity->add(std::make_shared<entities::component::Positional>(renderable.get()));
  }

}