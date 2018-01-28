#include "Cubes.hpp"
#include <Engine/Generator/Cube.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/OpenGLModel.h>

namespace scenes
{
  Cubes::Cubes(engine::render::Renderer &renderer)
  {
    auto geometry = engine::generator::Cube(1.f).generate();
    auto model = renderer.add(geometry, GL_TRIANGLES);
    /*auto instance = */renderer.add(*model);

#if 0
    shapes::Cube cube{ 1.0f };
    auto model = renderer.addGeometry(cube.vertices, cube.indices, cube.colors, GL_TRIANGLES);

    m_cubes.reserve(50);
    for (int i = 0; i < 50; ++i)
      addCube(renderer, model);
#endif
  }

  void Cubes::update(float dt)
  {
    for (int i = 0; i < m_cubes.size(); ++i)
    {
      if (i % 2 == 0)
        m_cubes.at(i).entity.orientation += 0.5f * dt;
    }

    for (auto &cube : m_cubes)
      cube.entity.update(dt);
    //m_cube1.position -= math::Vec3{ 0.05f, 0.f, 0.f } * dt;
    //m_cube1.update(dt);
    //m_cube2.position += math::Vec3{ 0.05f, 0.f, 0.f } * dt;
    //m_cube2.update(dt);
  }

  static float incPos{ 0.f };
  void Cubes::addCube(engine::render::Renderer &, size_t)
  {
    //auto &cube = m_cubes.emplace_back(CubeData{});
    //auto instance = renderer.addRenderable(model);
    //cube.pos.assign(&renderer, instance);
    //cube.entity.addComponent(&cube.pos);	// TODO: * Component becomes invalid when reallocation happens
    //cube.entity.position = { incPos, incPos, incPos };
    //incPos++;
  }

}