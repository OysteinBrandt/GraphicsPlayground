#include "Shader.h"
#include "Engine/Assert.h"
#include "Engine/Utilities/ResourcePath.h"
#include <filesystem>

#include <fstream>

namespace engine::render::opengl
{

  Shader::Shader(ShaderConfiguration config)
    : m_initialized(false), m_config(config)
  {
  }

  Shader::~Shader()
  {
    if (m_initialized)
    {
      unbind();
      glDetachShader(m_programId, m_vertexShaderId);
      glDetachShader(m_programId, m_fragmentShaderId);
      glDeleteProgram(m_programId);
      glDeleteShader(m_vertexShaderId);
      glDeleteShader(m_fragmentShaderId);
    }
  }

  void Shader::initialize()
  {
    ENGINE_ASSERT_EXCEPTION_IF(m_initialized, "Shader already initialized.");
    m_initialized = true;
    m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShader = readShaderCode(m_config.vertexShader);
    glShaderSource(m_vertexShaderId, 1, OglStringHelper(vertexShader), nullptr);

    std::string fragmentShader = readShaderCode(m_config.fragmentShader);
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

  void Shader::bind() const
  {
    glUseProgram(m_programId);
  }

  void Shader::unbind() const
  {
    glUseProgram(0);
  }

  void Shader::loadMVPMatrices(
    const math::Mat4& model,
    const math::Mat4& view,
    const math::Mat4& projection
  ) const
  {
    if (m_config.useCombinedMvpMatrix)
    {
      auto MVP = projection * view * model;
      GLint loc = glGetUniformLocation(m_programId, "MVP");
      ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named MVP");
      glUniformMatrix4fv(loc, 1, GL_FALSE, &MVP.x[0]);
    }
    else
    {
      GLint loc = glGetUniformLocation(m_programId, "model");
      ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named model");
      glUniformMatrix4fv(loc, 1, GL_FALSE, &model.x[0]);

      loc = glGetUniformLocation(m_programId, "view");
      ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named view");
      glUniformMatrix4fv(loc, 1, GL_FALSE, &view.x[0]);

      loc = glGetUniformLocation(m_programId, "projection");
      ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named projection");
      glUniformMatrix4fv(loc, 1, GL_FALSE, &projection.x[0]);
    }
  }

  void Shader::loadUniform3fv(std::string_view uniform_name, const math::Vec3& vec) const
  {
    GLint loc = glGetUniformLocation(m_programId, uniform_name.data());
    ENGINE_ASSERT_EXCEPTION_IF(loc == -1, "No uniform named '" + std::string(uniform_name) + "'");
    glUniform3fv(loc, 1, &vec.x);
  }

  std::string Shader::readShaderCode(const std::filesystem::path& shader) const
  {
    const auto resources = engine::bad::Resource::instance().path_copy();
    std::ifstream stream(resources / shader);
    if (!stream.good())
      ENGINE_ASSERT_WARNING("Failed to load shader: \"" + shader.u8string() + "\" from folder \"" + resources.u8string() + "\"");

    return std::string(std::istreambuf_iterator<char>{stream}, {});
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
      ENGINE_ASSERT_ERROR(log.c_str());
    }
  }

}