#include "Cubes.hpp"
#include <Engine/Generator/Cube.h>
#include <Engine/Render/OpenGL/Renderer.h>
#include <Engine/Render/OpenGL/OpenGLModel.h>
#include <Engine/Render/Color.h>

using engine::render::opengl::Texture;
namespace scenes
{
  Cubes::Cubes(engine::render::opengl::Renderer &renderer)
  {
    addAxis(renderer);

    auto geometry = engine::generator::Cube(0.5f).generate();
    auto model = renderer.add(geometry, GL_TRIANGLES);
    model->apply(Texture{ std::filesystem::u8path(u8"Resources") /= u8"UV-24-bit.bmp", Texture::FileFormat::Bmp });
    auto renderable = renderer.add(*model);

    auto &cube = m_cubes.emplace_back(CubeData{});
    cube.entity->position = { 0.f, 0.f, 0.f };
    cube.entity->add(std::make_shared<entities::component::Positional>(renderable.get()));
  }

  void Cubes::update(float dt)
  {
    //for (size_t i = 0; i < m_cubes.size(); ++i)
    //{
    //  if (i % 2 == 0)
    //    m_cubes.at(i).entity->orientation += 0.5f * dt;
    //}

    for (auto &cube : m_cubes)
      cube.entity->update(dt);
  }

  void Cubes::addAxis(engine::render::opengl::Renderer &renderer) const
  {
    std::vector<math::Vec3> axisLines{ {}, {1.f, 0.f, 0.f}, {}, {0.f, 1.f, 0.f}, {}, {0.f, 0.f, 1.f} };
    std::vector<math::Vec3> axisColors{ color::Red, color::Red, color::Green, color::Green, color::Blue, color::Blue };
    auto axisModel = renderer.add(axisLines, {}, axisColors, {}, GL_LINES);
    renderer.add(*axisModel);
  }

}