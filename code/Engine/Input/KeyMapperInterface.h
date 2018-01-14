#pragma once

namespace input
{
  class KeyMapperInterface
  {
  public:
    virtual int getKeyFor(int action) const = 0;
  };
}