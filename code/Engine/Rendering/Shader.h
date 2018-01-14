#pragma once

#include <GL/glew.h>

#include "Engine/Math/Mat4.h"
#include "Engine/DllHelper.h"
#include "Engine/Assert/AssertException.h"
#include <string>

namespace engine::render
{
	class OBR_API Shader
	{
		struct OglStringHelper {
			const char *p;
			OglStringHelper(const std::string& s) : p(s.c_str()) {}
			operator const char**() { return &p; }
		};

		bool m_initialized;
		GLuint m_vertexShaderId;
		GLuint m_fragmentShaderId;
		GLuint m_programId;
		std::string m_vertexShaderName;
		std::string m_fragmentShaderName;

	public:

		Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		~Shader();

		void initialize();
		void bind() const;
		void unbind() const;

		void loadMatrix(const math::Mat4 &matrix) const
		{
			GLint loc = glGetUniformLocation(m_programId, "MVP");
			ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named MVP");
			glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix.x[0]);
		}

		void loadColor(const math::Vec3 &color) const
		{
			GLint loc = glGetUniformLocation(m_programId, "custom_color");
			ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named custom_color");
			glUniform3fv(loc, 1, &color.x);
		}

	private:
		std::string readShaderCode(const std::string &fileName) const;
		void checkShaderStatus(GLuint shaderId) const;
		void checkProgramStatus(GLuint programId) const;
		void checkStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) const;
	};
}