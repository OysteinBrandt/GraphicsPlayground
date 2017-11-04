#include <GL/glew.h>
#include "OpenGLModel.h"
#include "Math/Vec3.h"

namespace engine::render
{

	OpenGLModel::OpenGLModel(const std::vector<math::Vec3>& vertices, const std::vector<unsigned short>& indices, GLenum renderMode)
		: m_renderMode(renderMode), m_vertexCount(indices.size())
	{
		glGenVertexArrays(1, &m_vaoID);
		glBindVertexArray(m_vaoID);

		glGenBuffers(1, &m_vertexBufferID);
		glGenBuffers(1, &m_indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::Vec3), vertices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);


		// http://www.informit.com/articles/article.aspx?p=2033340&seqNum=3
		// TODO: Consider using 'Packed Data Formats for Vertex Attributes'
		// eg. GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV
		/*
		"represent four-component data represented as ten bits for each of the first three components and two for the last,
		packed in reverse order into a single 32-bit quantity (a GLuint). GL_BGRA could just have easily been called GL_ZYXW"
		*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLModel::~OpenGLModel()
	{
		glDisableVertexAttribArray(0);
		glDeleteVertexArrays(1, &m_vaoID);
		glDeleteBuffers(1, &m_vertexBufferID);
		glDeleteBuffers(1, &m_indexBufferID);
	}

}