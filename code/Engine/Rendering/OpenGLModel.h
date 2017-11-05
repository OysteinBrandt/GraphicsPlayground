#pragma once

#include <vector>

namespace math { class Vec3; }

namespace engine::render
{
	class OpenGLModel
	{
		GLuint m_vaoID;
		GLuint m_vertexBufferID;
		GLuint m_indexBufferID;
		GLenum m_renderMode;
		GLsizei m_vertexCount;

	public:

		OpenGLModel(const std::vector<math::Vec3> &vertices, const std::vector<unsigned short> &indices, GLenum renderMode);
		~OpenGLModel();

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
	};
}