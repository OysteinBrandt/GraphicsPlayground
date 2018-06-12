#pragma once

#include <GL/glew.h>

#include "Engine/Math/Mat4.h"
#include "Engine/DllHelper.h"
#include "Engine/Assert/AssertException.h"
#include <string>

namespace engine::render::opengl
{
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
    std::string m_vertexShaderName;
    std::string m_fragmentShaderName;

  public:

    ENGINE_API Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    ENGINE_API ~Shader();

    void initialize();
    void bind() const;
    void unbind() const;

    void loadMatrix(const math::Mat4 &matrix) const;
    void loadColor(const math::Vec3 &color) const;

  private:
    std::string readShaderCode(const std::string &fileName) const;
    void checkShaderStatus(GLuint shaderId) const;
    void checkProgramStatus(GLuint programId) const;
    void checkStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) const;
  };
}