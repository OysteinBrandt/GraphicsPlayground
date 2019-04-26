
#include "Texture.h"

#include "Engine/Assert.h"
#include <fstream>
#include <memory>

namespace engine::render::opengl
{
  Texture::Texture(const std::filesystem::path& filePath, FileFormat fileType)
  {
    switch (fileType)
    {
    case FileFormat::Bmp:
      loadBmp(filePath);
    break;

    default:
      ENGINE_ASSERT_WARNING("Texture file format not supported!");
      break;
    }
  }

  Texture::~Texture()
  {
    if (m_texture != 0)
      glDeleteTextures(1, &m_texture);
  }

  void Texture::bind() const
  {
    if (m_texture != 0)
      glBindTexture(GL_TEXTURE_2D, m_texture);
  }

  void Texture::unbind() const
  {
    if (m_texture != 0)
      glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Texture::install()
  {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    if (m_data.empty())
    {
      // 1x1 pixel texture of 'white' that acts as default (no special handling needed in shader)
      float pixels[] = { 1.0f, 1.0f, 1.0f };
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, pixels);
    }
    else
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, m_data.data());

      // If known number of mipmaps
      //glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
      //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

      if (GL_ARB_framebuffer_object)
        glGenerateMipmap(GL_TEXTURE_2D);
      else
        ENGINE_ASSERT_WARNING("Automatic mipmap generation is not supported!");
        
        //glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        //gluBuild2DMipmaps

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    unbind();
  }

  void Texture::loadBmp(const std::filesystem::path& filePath)
  {
    std::ifstream fileStream(filePath, std::ios::binary);
    if (!fileStream.good())
    {
      ENGINE_ASSERT_WARNING("Failed to load texture from: \"" + filePath.u8string() + "\"");
      return;
    }

    char header[54];
    fileStream.get(header, 54);

    if (header[0] != 'B' || header[1] != 'M')
    {
      ENGINE_ASSERT_WARNING("File did not contain values expected from BMP format!");
      return;
    }

    int dataPos = *reinterpret_cast<int*>(&header[0x0A]);
    int size = *reinterpret_cast<int*>(&header[0x22]);
    m_width = *reinterpret_cast<int*>(&header[0x12]);
    m_height = *reinterpret_cast<int*>(&header[0x16]);

    if (size == 0)
      size = m_width * m_height * 3;
    if (dataPos == 0)
      dataPos = 54;

    m_data = std::string(size, '\0');
    fileStream.seekg(dataPos);
    fileStream.read(m_data.data(), size);
  }
}