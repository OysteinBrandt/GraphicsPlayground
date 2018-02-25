#pragma once

#include <GL/glew.h>

#include "Texture.h"
#include "Engine/Math/Vec2.h"

#include <vector>

namespace math { class Vec3; }

namespace engine::render::opengl
{
  class OpenGLModel
  {
    Texture m_texture;
    GLuint m_vaoID;
    std::vector<GLuint> m_vboIDs;
    std::vector<unsigned int> m_attributes;
    GLenum m_renderMode;
    GLsizei m_vertexCount;
    bool m_renderOutline;
    bool m_usesIndices;

  public:

    OpenGLModel(const std::vector<math::Vec3> &vertices, const std::vector<unsigned short> &indices,
      const std::vector<math::Vec3> &colors, const std::vector<math::Vec2>& textureCoords, GLenum renderMode);
    ~OpenGLModel();

    void bind() const;
    void unbind() const;

    ENGINE_API void apply(Texture texture);

    GLenum renderMode() const
    {
      return m_renderMode;
    }

    GLuint vaoID() const
    {
      return m_vaoID;
    }

    GLsizei vertexCount() const
    {
      return m_vertexCount;
    }

    void renderOutline(bool outline)
    {
      m_renderOutline = outline;
    }

    bool renderOutline() const
    {
      return m_renderOutline;
    }

    bool usesIndices() const
    {
      return m_usesIndices;
    }

  private:

    template <typename Container>
    void storeDataInAttributeList(GLuint attributeNumber, GLint containerLenght, const Container& container, GLboolean normalized);
    void bindIndicesBuffer(const std::vector<GLushort> &indices);
  };
}