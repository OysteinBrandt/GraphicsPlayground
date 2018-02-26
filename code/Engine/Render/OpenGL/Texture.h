#pragma once

#include <GL/glew.h>
#include "Engine/DllHelper.h"

#include <string>

namespace engine::render::opengl
{
  class Texture
  {
  public:
    // TODO: Consider using extension of filename to determine file format
    enum class FileFormat
    {
      Png,
      Bmp
    };

  private:

    GLuint m_texture{ 0 };
    int m_width{ 0 };
    int m_height{ 0 };
    std::string m_data;

  public:

    // TODO: Use std::filesystem::path when supported equally on all compilers
    ENGINE_API Texture(const std::string& file, FileFormat fileType);

    Texture()
    { }

    // Copy constructor
    ENGINE_API Texture(Texture& other)
      : m_texture(other.m_texture), m_width(other.m_width),
        m_height(other.m_height), m_data(other.m_data)
    { }

    // Copy assignment
    ENGINE_API Texture& operator=(const Texture& other)
    {
      m_texture = other.m_texture;
      m_width = other.m_width;
      m_height = other.m_height;
      m_data = other.m_data;
      return *this;
    }

    // Move constructor
    ENGINE_API Texture(Texture&& other)
      : m_texture(other.m_texture), m_width(other.m_width),
        m_height(other.m_height), m_data(std::move(other.m_data))
    { }

    // Move assignment
    ENGINE_API Texture& operator=(Texture&& other)
    {
      m_texture = other.m_texture;
      m_width = other.m_width;
      m_height = other.m_height;
      m_data = std::move(other.m_data);
      return *this;
    }

    ENGINE_API ~Texture();

    void bind() const;
    void unbind() const;

    // TODO: Consider a layer of abstraction for general graphics API
    // TODO: Prevent user from having access to bind(), unbind(), install() ?
    void install();

  private:

    void loadBmp(const std::string& file);
  };
}