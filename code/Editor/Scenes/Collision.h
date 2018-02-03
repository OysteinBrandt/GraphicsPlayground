#pragma once

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Positional.h>
#include <memory>

namespace engine::render::opengl { class Renderer; }
namespace engine::render::opengl { class OpenGLModel; }

namespace scenes
{
  struct Sphere
  {
    Sphere() : entity(std::make_unique<entities::Entity>())
    {}

    // TODO: Investigate reallocation problems when using stack
    std::unique_ptr<entities::Entity> entity;
  };

  class Collision
  {
    std::vector<Sphere> m_spheres;

  public:
    Collision(engine::render::opengl::Renderer &renderer);
    void update(float dt);

  private:

    void addSphere(engine::render::opengl::Renderer& renderer, const engine::render::opengl::OpenGLModel& model, const math::Vec3& pos);
  };
}