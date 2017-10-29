#pragma once

#include "DllHelper.h"

namespace entities
{
	class Entity;
	class OBR_API Component
	{
		friend class Entity;
		Entity *m_parent;
	public:
		Entity *getParent() const
		{
			return m_parent;
		}

		virtual void update() {}
	};
}