#include "ControllerComponent.h"

#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Physics.h>
#include <Engine/Math/Vec3.h>
#include "ApplicationParam.h"

using entities::component::Physics;

ControllerComponent::ControllerComponent(const ApplicationParam& application, entities::component::Physics& physics)
  : m_application(application), m_physics(physics)
{ }

void ControllerComponent::update(float)
{
  const float angularVelocity{ 0.001f };
  if (m_application.input.keyboard.A.isDown)
    m_physics.angularVelocity = angularVelocity;
  else if (m_application.input.keyboard.D.isDown)
    m_physics.angularVelocity = -angularVelocity;
  else
    m_physics.angularVelocity = 0.0f;

  if (m_application.input.keyboard.W.isDown)
  {
    const auto orientation = getParent()->orientation;
    //auto directionToAccel = math::Mat3::rotate(orientation, math::Mat3::Axis::) * frontDirectionOfEntity;
    m_physics.acceleration = math::Vec3{ -sinf(orientation), cosf(orientation) };
  }
}
