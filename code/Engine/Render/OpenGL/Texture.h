#pragma once

#include <GL/glew.h>
#include "Engine/DllHelper.h"

#include <string>

namespace engine::render::opengl
{
  class Texture
  {
  public:
    enum class FileType
    {
      Png,
      Bmp
    };

    GLuint m_texture;
    bool m_default;

    // TODO: Use std::filesystem::path when supported by all compilers
    ENGINE_API Texture(std::string, FileType) : m_texture(0), m_default(false)
    { }

    Texture() : m_texture(0), m_default(true)
    { }

    ENGINE_API ~Texture()
    {
      if (m_texture != 0)
        glDeleteTextures(1, &m_texture);
    }

    // TODO: Consider a layer of abstraction for general graphics API
    void install()
    {
      glGenTextures(1, &m_texture);
      glBindTexture(GL_TEXTURE_2D, m_texture);
      //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // TODO: Investigate

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  //GL_REPEAT
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // TODO: Imvestigate

      if (m_default)
      {
        // 1x1 pixel texture of 'white' that acts as default (no special handling needed in shader)
        float pixels[] = { 1.0f, 1.0f, 1.0f };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, pixels);
      }
      else
      {
        // TODO: Check if texture is flipped on one axis?
        float pixels[] = {
          0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
        };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
      }

#if 0
      int width, height;
      unsigned char* image = loadImage("img.png", &width, &height, 0, SOIL_LOAD_RGB);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
#endif

      glGenerateMipmap(GL_TEXTURE_2D);  // Texture must be loaded
      unbind();
    }

    void bind() const
    {
      if (m_texture != 0)
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    void unbind() const
    {
      if (m_texture != 0)
        glBindTexture(GL_TEXTURE_2D, 0);
    }
  };
}