#include "Antennas.h"
#include <Engine/Generator/Cube.h>
#include <Engine/Render/OpenGL/Renderer.h>
#include <Engine/Render/OpenGL/OpenGLModel.h>
#include <Engine/Render/Color.h>
#include <Engine/Model/Loader.h>
#include <Engine/Utilities/ResourcePath.h>

using engine::render::opengl::Texture;
namespace scenes
{
  Antennas::Antennas(engine::render::opengl::Renderer &renderer)
  {
    addAxis(renderer);

    if (const auto antennaGeometry = engine::ModelLoader::open_from_resource(std::filesystem::u8path("placeholder-antenna-01.obj")))
    {
      auto antennaModel = renderer.add(
        antennaGeometry->vertices,
        antennaGeometry->indices,
        antennaGeometry->normals,
        antennaGeometry->colors,
        antennaGeometry->textureCoords,
        GL_TRIANGLES
      );
      antennaModel->apply(Texture(engine::bad::Resource::instance().path_copy()  /= u8"UV-24-bit.bmp", Texture::FileFormat::Bmp ));
      auto renderableAntenna = renderer.add(*antennaModel);
      auto &antenna = m_antennas.emplace_back(Antenna{});
      antenna.entity->position = { 1.f, 0.f, 0.f };
      antenna.entity->orientation = 3.14f / 2.f;
      //TODO: Scale?
      antenna.entity->add(std::make_shared<entities::component::Positional>(renderableAntenna.get()));
    }
  }

  void Antennas::update(float dt)
  {
    for (auto &a : m_antennas )
      a.entity->update(dt);
  }

  void Antennas::addAxis(engine::render::opengl::Renderer &renderer) const
  {
    std::vector<math::Vec3> axisLines{ {}, {100.f, 0.f, 0.f}, {}, {0.f, 100.f, 0.f}, {}, {0.f, 0.f, 100.f} };
    std::vector<math::Vec3> axisColors{ color::Red, color::Red, color::Green, color::Green, color::Blue, color::Blue };
    auto axisModel = renderer.add(axisLines, {}, {}, axisColors, {}, GL_LINES);
    renderer.add(*axisModel);
  }

}