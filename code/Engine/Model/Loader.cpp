#include "Loader.h"

#include "ObjLoader.h"
#include "Engine/Assert.h"
#include "Engine/Utilities/ResourcePath.h"

namespace engine
{
  // TODO(obr): Idealy we would not need this translator. The data is esentially copied into another structure.
  //            Consider writing our own .obj loader
  std::optional<Model> translateOjbToEngineModel(const std::filesystem::path& file)
  {
    objl::Loader loader;
#ifndef ENGINE_DEBUG
    #undef OBJL_CONSOLE_OUTPUT
#endif

    if (loader.LoadFile(file.string()))
    {
      Model m;

      for (int i = 0; i < loader.LoadedMeshes.size(); ++i)
      {
        const auto& currentMesh = loader.LoadedMeshes[i];
        std::transform(currentMesh.Indices.begin(), currentMesh.Indices.end(), std::back_inserter(m.indices), [](const auto val) { return static_cast<unsigned short>(val); });

        for (const auto& v : currentMesh.Vertices)
        {
          m.vertices.push_back({ v.Position.X, v.Position.Y, v.Position.Z });
          m.normals.push_back({ v.Normal.X, v.Normal.Y, v.Normal.Z });
        }
      }
      return m;
    }
    else
    {
      ENGINE_ASSERT_WARNING("Failed to load .obj file from path: '" + file.string() + "'");
      return {};
    }
  }

  std::optional<Model> ModelLoader::open_from_resource(const std::filesystem::path& filepath)
  {
    const auto extension = filepath.extension();
    if (extension == ".obj") {
      return translateOjbToEngineModel(engine::bad::Resource::instance().path() / filepath);
    }

    return {};
  }
}