#include "Engine.h"

#include <GL/glew.h>
#include "Engine/Assert/AssertException.h"

namespace engine
{
  void init(Renderer renderer)
  {
    switch (renderer)
    {
    case engine::Renderer::OpenGL:
    {
      GLenum errorCode = glewInit();
      ENGINE_ASSERT_EXCEPTION_IF(errorCode != GLEW_NO_ERROR, "Failed to initialize glew.");
    } break;

    default:
      ENGINE_ASSERT_EXCEPTION("Engine not supported!");
      break;
    }
  }

  void init(Renderer renderer, std::ostream& os, bool outputSuccess)
  {
    switch (renderer)
    {
    case engine::Renderer::OpenGL:
    {
      GLenum errorCode = glewInit();
      if (errorCode != GLEW_NO_ERROR)
        os << "Failed to initialize glew!";
      else if (outputSuccess)
        os << "Successfully initialized glew!";
    } break;

    default:
      os << "Engine not supported!";
      break;
    }
  }

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::update()
{

}

void Engine::render()
{

}
}