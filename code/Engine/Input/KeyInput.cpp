#include "KeyInput.h"
#include "KeyMapperInterface.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // TODO: Make platform independent?
#include "Engine/Assert/AssertException.h"

namespace input
{

  KeyInput::KeyInput(const KeyMapperInterface &keyMapper, int maxActionValue)
  {
    m_keyMapper = &keyMapper;
    m_maxActionValue = maxActionValue;
    ENGINE_ASSERT_EXCEPTION_IF(m_maxActionValue <= 0, "Should have at least one action");
  }

  void KeyInput::update()
  {
    m_actionsThisFrame = 0;
    int possibleAction{ 1 };
    while (possibleAction != m_maxActionValue)
    {
      int key = m_keyMapper->getKeyFor(possibleAction);
      if (GetAsyncKeyState(key))
        m_actionsThisFrame |= possibleAction;
      possibleAction <<= 1;
    }
  }

  bool KeyInput::isActionsHot(int actions) const
  {
    return (m_actionsThisFrame & actions) == actions;
  }

}