#pragma once

#include "Engine/DllHelper.h"

namespace input
{
  class KeyMapperInterface;
  class ENGINE_API KeyInput
  {
    const KeyMapperInterface *m_keyMapper;
    int m_maxActionValue;
    int m_actionsThisFrame;

  public:
    KeyInput(const KeyMapperInterface &keyMapper, int maxActionValue);

    ENGINE_DEPRECATED void update();
    int actionsThisFrame() const
    {
      return m_actionsThisFrame;
    }

    ENGINE_DEPRECATED bool isActionsHot(int actions) const;
  };
}