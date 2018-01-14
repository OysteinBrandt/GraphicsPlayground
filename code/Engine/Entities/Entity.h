#pragma once

#include <Engine/Math/Vec3.h>
#include <Engine/DllHelper.h>
#include <vector>

namespace entities
{
	class Component;
	class OBR_API Entity
	{
		std::vector<Component*> m_components;

	public:
		math::Vec3 position;
		float orientation;

		Entity();
		void addComponent(Component *component);
		void update(float dt);

		template<class T>
		T* getComponent() const;
	};

	template<class T>
	T* Entity::getComponent() const
	{
		for (const auto &component : m_components)
		{
			T* ret = dynamic_cast<T*>(component);
			if (ret != nullptr)
				return ret;
		}

		return nullptr;
	}
}
