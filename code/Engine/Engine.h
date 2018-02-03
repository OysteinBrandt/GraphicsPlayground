#pragma once

#include "Engine/DllHelper.h"
#include <ostream>

namespace engine
{
  enum class Renderer
  {
    OpenGL
  };

  class OBR_API Engine
  {
  public:

    Engine();
    ~Engine();

    void update();
    void render();
  };

  OBR_API void init(Renderer renderer);
  OBR_API void init(Renderer renderer, std::ostream& os, bool outputSuccess = false);

}