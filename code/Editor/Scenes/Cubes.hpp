#pragma once

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Positional.h>
#include <Engine/Entities/Components/Physics.h>
#include <Engine/Render/Renderable.h>

namespace engine::render::opengl { class Renderer; }

struct CubeData
{
  entities::Entity entity;
};

namespace scenes
{
  class Cubes
  {
    std::vector<CubeData> m_cubes;

  public:

    Cubes(engine::render::opengl::Renderer &renderer);
    void update(float dt);

  private:

    void addCube(engine::render::opengl::Renderer &renderer, size_t model);
  };
}