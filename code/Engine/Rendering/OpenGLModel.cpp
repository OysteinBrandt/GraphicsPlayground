#include <GL/glew.h>
#include "OpenGLModel.h"
#include "Math/Vec3.h"

namespace engine::render
{

	OpenGLModel::OpenGLModel(const std::vector<math::Vec3>& vertices, const std::vector<unsigned short>& indices,
		const std::vector<math::Vec3> &colors, GLenum renderMode)
		: m_renderMode(renderMode), m_vertexCount(indices.size()), m_renderOutline{false}
	{
		glGenVertexArrays(1, &m_vaoID);
		glBindVertexArray(m_vaoID);

		storeDataInAttributeList(0, vertices, GL_FALSE);
		if (!colors.empty())
			storeDataInAttributeList(1, colors, GL_TRUE);
		bindIndicesBuffer(indices);

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
	}

	void OpenGLModel::unbind() const
	{
		for (const auto &attribute : m_attributes)
			glDisableVertexAttribArray(attribute);
		glBindVertexArray(0);
	}

	void OpenGLModel::storeDataInAttributeList(GLuint attributeNumber, const std::vector<math::Vec3>& data, GLboolean normalized)
	{
		GLuint vboId;
		m_vboIDs.push_back(vboId);
		glGenBuffers(1, &m_vboIDs.back());
		glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs.back());
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(math::Vec3), data.data(), GL_STATIC_DRAW);
		// http://www.informit.com/articles/article.aspx?p=2033340&seqNum=3
		// https://www.khronos.org/opengl/wiki/Vertex_Specification_Best_Practices
		// TODO: Consider using 'Packed Data Formats for Vertex Attributes'
		// eg. GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV
		/*
		"represent four-component data represented as ten bits for each of the first three components and two for the last,
		packed in reverse order into a single 32-bit quantity (a GLuint). GL_BGRA could just have easily been called GL_ZYXW"
		*/
		m_attributes.push_back(attributeNumber);
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, normalized, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLModel::bindIndicesBuffer(const std::vector<GLushort> &indices)
	{
		GLuint vboId;
		m_vboIDs.push_back(vboId);
		glGenBuffers(1, &m_vboIDs.back());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIDs.back());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
	}
}