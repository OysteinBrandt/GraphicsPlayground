#pragma once

#include <GL/glew.h>
#include "DllHelper.h"
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

		GLuint m_vertexShaderId;
		GLuint m_fragmentShaderId;
		GLuint m_programId;

	public:

		Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		~Shader();

		void useProgram() const;

	private:
		std::string readShaderCode(const std::string &fileName) const;
		void checkShaderStatus(GLuint shaderId) const;
		void checkProgramStatus(GLuint programId) const;
		void checkStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) const;
	};
}