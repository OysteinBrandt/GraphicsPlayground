#pragma once

#include "Engine/Math/Vec2.h"
#include "Engine/Math/Vec3.h"
#include "Engine/DllHelper.h"
#include <vector>
#include <filesystem>
#include <optional>

namespace engine
{
  struct Model
  {
    std::vector<math::Vec3> vertices;
    std::vector<unsigned short> indices;
    std::vector<math::Vec3> normals;
    std::vector<math::Vec3> colors;
    std::vector<math::Vec2> textureCoords;
  };

  class ModelLoader
  {
  public:
    ENGINE_API static std::optional<Model> open_from_resource(const std::filesystem::path& filepath);
  };
}
