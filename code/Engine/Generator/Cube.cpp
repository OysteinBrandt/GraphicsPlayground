#include "Cube.h"
#include <array>

namespace engine::generator
{
  Cube::Cube(float size) : m_size(size)
  { }

  Geometry Cube::generate() const
  {
    std::array<math::Vec3, 8> vertices
    {{
      {-m_size, -m_size,  m_size },
      { m_size, -m_size,  m_size },
      { m_size,  m_size,  m_size },
      {-m_size,  m_size,  m_size },
      {-m_size, -m_size, -m_size },
      { m_size, -m_size, -m_size },
      { m_size,  m_size, -m_size },
      {-m_size,  m_size, -m_size }
    }};

    std::array<math::Vec2, 4> texCoords
    {{
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    }};

    std::array<math::Vec3, 6> normals
    {{
      { 0,  0,  1},
      { 1,  0,  0},
      { 0,  0, -1},
      {-1,  0,  0},
      { 0,  1,  0},
      { 0, -1,  0}
    }};

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
    for (auto index : indices)
      geometry.vertices.push_back(vertices.at(index));

    geometry.normals.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++)
      geometry.normals.push_back(normals[i / 6]);

    geometry.colors = std::vector<math::Vec3>(36, math::Vec3{ 1.f, 1.f, 1.f });

    geometry.textureCoords.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++)
      geometry.textureCoords.push_back(texCoords[texInds[i % 6]]);

    return geometry;
  }
}