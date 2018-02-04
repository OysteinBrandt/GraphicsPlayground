#pragma once

#include "Engine/DllHelper.h"

namespace entities
{
  class Entity;
  class ENGINE_API Component
  {
    friend class Entity;
    Entity *m_parent;
  public:

    Entity *getParent() const
    {
      return m_parent;
    }

    virtual void update(float) {}
  };
}