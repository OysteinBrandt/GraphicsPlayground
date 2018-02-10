#pragma once

#include <Engine/Entities/Component.h>

struct ApplicationParam;
namespace entities::component { class Physics; }

class ControllerComponent : public entities::Component
{
  const ApplicationParam& m_application;
  entities::component::Physics& m_physics;

public:
  ControllerComponent(const ApplicationParam &application, entities::component::Physics& physics);

  void update(float) override;
};