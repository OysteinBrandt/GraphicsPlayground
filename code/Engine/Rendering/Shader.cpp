#include "Shader.h"
#include "Assert/AssertException.h"

#include <fstream>

namespace engine::render
{

	Shader::Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
	{
		m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexShader = readShaderCode(vertexShaderPath);
		glShaderSource(m_vertexShaderId, 1, OglStringHelper(vertexShader), nullptr);

		std::string fragmentShader = readShaderCode(fragmentShaderPath);
		glShaderSource(m_fragmentShaderId, 1, OglStringHelper(fragmentShader), nullptr);

		glCompileShader(m_vertexShaderId);
		checkShaderStatus(m_vertexShaderId);

		glCompileShader(m_fragmentShaderId);
		checkShaderStatus(m_fragmentShaderId);

		m_programId = glCreateProgram();
		glAttachShader(m_programId, m_vertexShaderId);
		glAttachShader(m_programId, m_fragmentShaderId);
		glLinkProgram(m_programId);

		// TODO: Validate that this function works
		checkProgramStatus(m_programId);
	}

	Shader::~Shader()
	{
		glDetachShader(m_programId, m_vertexShaderId);
		glDetachShader(m_programId, m_fragmentShaderId);

		glDeleteShader(m_vertexShaderId);
		glDeleteShader(m_fragmentShaderId);
	}

	void Shader::useProgram() const
	{
		glUseProgram(m_programId);
	}

	std::string Shader::readShaderCode(const std::string &fileName) const
	{
		std::ifstream stream("D:/src/GraphicsPlayground/Resources/Shaders/" + fileName);
		if (!stream.good())
			ENGINE_ASSERT_EXCEPTION("Failed to load shader: " + fileName);

		return std::string(
			(std::istreambuf_iterator<char>(stream)),
			std::istreambuf_iterator<char>());
	}

	void Shader::checkShaderStatus(GLuint shaderId) const
	{
		checkStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	}

	void Shader::checkProgramStatus(GLuint programId) const
	{
		checkStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	}

	void Shader::checkStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) const
	{
		GLint status;
		objectPropertyGetterFunc(objectId, statusType, &status);
		if (status != GL_TRUE)
		{
			GLint infoLogLength;
			objectPropertyGetterFunc(objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLsizei bufferSize;
			std::string log;
			log.reserve(infoLogLength);
			getInfoLogFunc(objectId, infoLogLength, &bufferSize, &log[0]);
			ENGINE_ASSERT_EXCEPTION(log.c_str());
		}
	}

}