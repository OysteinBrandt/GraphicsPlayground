#include "Entity.h"
#include "Component.h"

namespace entities
{

Entity::Entity() : orientation{0.0f}
{
}

void Entity::addComponent(Component * component)
{
	m_components.push_back(component);
	component->m_parent = this;
}

void Entity::update(float dt)
{
	for (const auto &component : m_components)
		component->update(dt);
}

}