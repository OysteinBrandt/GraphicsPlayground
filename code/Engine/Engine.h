#pragma once

#include "Engine/DllHelper.h"

namespace obr
{
  class Engine
  {
  private:

  public:
    OBR_API Engine();
    OBR_API ~Engine();

    OBR_API void update();
    OBR_API void render();
  };

}