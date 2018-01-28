#pragma once

#include <Engine/Math/Vec3.h>
#include <Engine/DllHelper.h>
#include <vector>
#include <memory>

namespace entities
{
  class Component;
  class OBR_API Entity
  {
    std::vector<std::shared_ptr<Component>> m_components;

  public:
    math::Vec3 position;
    float orientation;

    Entity();
    void add(const std::shared_ptr<Component>& component);
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
