#pragma once

#include "Engine/DllHelper.h"
#include <ostream>

namespace engine
{
  enum class Renderer
  {
    OpenGL
  };

  class ENGINE_API Engine
  {
  public:

    Engine();
    ~Engine();

    void update();
    void render();
  };

  ENGINE_API void init(Renderer renderer);
  ENGINE_API void init(Renderer renderer, std::ostream& os, bool outputSuccess = false);

}