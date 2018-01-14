#pragma once

#include "Engine/DllHelper.h"

namespace input
{
	class KeyMapperInterface;
	class OBR_API KeyInput
	{
		const KeyMapperInterface *m_keyMapper;
		int m_maxActionValue;
		int m_actionsThisFrame;

	public:
		KeyInput(const KeyMapperInterface &keyMapper, int maxActionValue);

		void update();
		int actionsThisFrame() const
		{
			return m_actionsThisFrame;
		}

		bool isActionsHot(int actions) const;
	};
}