#pragma once

#include <GL/glew.h>

#include "Engine/Math/Mat4.h"
#include "Engine/DllHelper.h"
#include "Engine/Assert/AssertException.h"
#include <string>
#include <filesystem>

namespace engine::render::opengl
{
  enum class ShaderType
  {
    DEFAULT,
    PHONG
  };

  struct ShaderConfiguration
  {
    std::filesystem::path vertexShader{};
    std::filesystem::path fragmentShader{};
    bool useCombinedMvpMatrix{ true };
    ShaderType type{ ShaderType::DEFAULT };
  };

  /***************************************************************************/
  
  class Shader
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
    ShaderConfiguration m_config;

  public:

    ENGINE_API Shader(ShaderConfiguration config);
    ENGINE_API ~Shader();

    void initialize();
    void bind() const;
    void unbind() const;

    ShaderType type() const {
      return m_config.type;
    }

    void loadMVPMatrices(
      const math::Mat4& model,
      const math::Mat4& view,
      const math::Mat4& projection
    ) const;

    void loadUniform3fv(std::string_view uniform_name, const math::Vec3& vec) const;

  private:
    std::string readShaderCode(const std::filesystem::path& shader) const;
    void checkShaderStatus(GLuint shaderId) const;
    void checkProgramStatus(GLuint programId) const;
    void checkStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) const;
  };
}