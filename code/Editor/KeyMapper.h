#pragma once

#include <Engine/Input/KeyMapperInterface.h>

namespace input
{
  class KeyMapper : public KeyMapperInterface
  {
  public:
    int getKeyFor(int action) const;
  };
}