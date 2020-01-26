
#include "OpenGLModel.h"
#include "Engine/Math/Vec3.h"

namespace engine::render::opengl
{

  OpenGLModel::OpenGLModel(
    const std::vector<math::Vec3>& vertices,
    const std::vector<unsigned short>& indices,
    const std::vector<math::Vec3> &normals,
    const std::vector<math::Vec3> &colors,
    const std::vector<math::Vec2>& textureCoords,
    GLenum renderMode
  )
    : m_renderMode(renderMode), m_renderOutline{ false }, m_usesIndices{ false }
  {
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    storeDataInAttributeList(0, 3, vertices, GL_FALSE);

    if (!normals.empty())
      storeDataInAttributeList(1, 3, normals, GL_FALSE);
    if (!colors.empty())
      storeDataInAttributeList(2, 3, colors, GL_TRUE);
    if (!textureCoords.empty())
      storeDataInAttributeList(3, 2, textureCoords, GL_FALSE);
    else
    { // Default texture is used to prevent special handling in shader
      m_texture.install();
      std::vector<math::Vec2> defaultTextureCoordinates(vertices.size(), { 0.f, 0.f });
      storeDataInAttributeList(4, 2, defaultTextureCoordinates, GL_FALSE);
    }

    if (!indices.empty())
    {
      m_vertexCount = indices.size();
      bindIndicesBuffer(indices);
    }
    else
      m_vertexCount = vertices.size();

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  OpenGLModel::~OpenGLModel()
  {
    glDeleteVertexArrays(1, &m_vaoID);
    glDeleteBuffers(m_vboIDs.size(), m_vboIDs.data());
  }

  void OpenGLModel::bind() const
  {
    glBindVertexArray(m_vaoID);
    for (const auto &attribute : m_attributes)
      glEnableVertexAttribArray(attribute);

    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();
  }

  void OpenGLModel::unbind() const
  {
    m_texture.unbind();

    for (const auto &attribute : m_attributes)
      glDisableVertexAttribArray(attribute);
    glBindVertexArray(0);
  }

  void OpenGLModel::apply(Texture texture)
  {
    m_texture = std::move(texture);
    m_texture.install();
  }

  template <typename Container>
  void OpenGLModel::storeDataInAttributeList(GLuint attributeNumber, GLint containerLenght, const Container& container, GLboolean normalized)
  {
    GLuint vboId;
    m_vboIDs.push_back(vboId);
    glGenBuffers(1, &m_vboIDs.back());
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs.back());
    glBufferData(GL_ARRAY_BUFFER, container.size() * sizeof(Container::value_type), container.data(), GL_STATIC_DRAW);
    // http://www.informit.com/articles/article.aspx?p=2033340&seqNum=3
    // https://www.khronos.org/opengl/wiki/Vertex_Specification_Best_Practices
    // TODO: Consider using 'Packed Data Formats for Vertex Attributes', also; packed buffer with offsetof
    // eg. GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV
    /*
    "represent four-component data represented as ten bits for each of the first three components and two for the last,
    packed in reverse order into a single 32-bit quantity (a GLuint). GL_BGRA could just have easily been called GL_ZYXW"
    */
    m_attributes.push_back(attributeNumber);
    glVertexAttribPointer(attributeNumber, containerLenght, GL_FLOAT, normalized, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void OpenGLModel::bindIndicesBuffer(const std::vector<GLushort> &indices)
  {
    m_usesIndices = true;
    GLuint vboId;
    m_vboIDs.push_back(vboId);
    glGenBuffers(1, &m_vboIDs.back());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIDs.back());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
  }
}