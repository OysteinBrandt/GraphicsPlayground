#pragma once

#include <vector>

namespace math { class Vec3; }

namespace engine::render
{
	class OpenGLModel
	{
		GLuint m_vaoID;
		std::vector<GLuint> m_vboIDs;
		GLenum m_renderMode;
		GLsizei m_vertexCount;
		bool m_renderOutline;

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

		void renderOutline(bool outline)
		{
			m_renderOutline = outline;
		}

		bool renderOutline() const
		{
			return m_renderOutline;
		}

	private:

		void storeDataInAttributeList(GLuint attributeNumber, const std::vector<math::Vec3>& data);
		void bindIndicesBuffer(const std::vector<GLushort> &indices);
	};
}