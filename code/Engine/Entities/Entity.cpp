#include "Entity.h"
#include "Component.h"

namespace entities
{

  Entity::Entity() : orientation{ 0.0f }
  {
  }

  void Entity::addComponent(Component * component)
  {
    // TODO: Make API less error prone by not allowing multiple components of same type?
    // eg. Disallow one entity to have two Positional components?
    m_components.push_back(component);
    component->m_parent = this;
  }

  void Entity::update(float dt)
  {
    for (const auto &component : m_components)
      component->update(dt);
  }

}