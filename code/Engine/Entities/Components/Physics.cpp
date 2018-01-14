#include "Physics.h"
#include "Engine/Entities/Entity.h"

namespace entities::component
{

  void Physics::update(float dt)
  {
    velocity += acceleration * dt;
    getParent()->position += velocity * dt;
    getParent()->orientation += angularVelocity;
    acceleration = math::Vec3{};
  }

}