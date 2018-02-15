#include "Cube.h"
#include <array>

namespace engine::generator
{
  Cube::Cube(float size) : m_size(size)
  { }

  Geometry Cube::generate() const
  {
    std::array<math::Vec3, 8> vertices
    {
      math::Vec3{-1, -1,  1 },
      math::Vec3{ 1, -1,  1 },
      math::Vec3{ 1,  1,  1 },
      math::Vec3{-1,  1,  1 },
      math::Vec3{-1, -1, -1 },
      math::Vec3{ 1, -1, -1 },
      math::Vec3{ 1,  1, -1 },
      math::Vec3{-1,  1, -1 }
    };

    std::array<math::Vec2, 4> texCoords
    {
      math::Vec2{0, 0},
      math::Vec2{1, 0},
      math::Vec2{1, 1},
      math::Vec2{0, 1}
    };

    std::array<math::Vec3, 6> normals
    {
      math::Vec3{ 0,  0,  1},
      math::Vec3{ 1,  0,  0},
      math::Vec3{ 0,  0, -1},
      math::Vec3{-1,  0,  0},
      math::Vec3{ 0,  1,  0},
      math::Vec3{ 0, -1,  0}
    };

    std::array<unsigned short, 36> indices
    {
      0, 1, 3, 3, 1, 2,
      1, 5, 2, 2, 5, 6,
      5, 4, 6, 6, 4, 7,
      4, 0, 7, 7, 0, 3,
      3, 2, 7, 7, 2, 6,
      4, 5, 0, 0, 5, 1
    };

    std::array<int, 6> texInds{ 0, 1, 3, 3, 1, 2 };

    Geometry geometry;
    geometry.vertices.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++)
      geometry.vertices.push_back(vertices[indices[i]]);

    geometry.normals.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++)
      geometry.normals.push_back(normals[indices[i / 6]]);

    geometry.colors = std::vector<math::Vec3>(36, math::Vec3{ 0.f, 1.f, 0.f });

    geometry.textureCoords.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++)
      geometry.textureCoords.push_back(texCoords[texInds[i % 6]]);

    return geometry;
  }
}