#pragma once

#include <Engine/Entities/Component.h>

namespace engine::render { class Camera; }
namespace details { struct Window; }
struct ApplicationParam;

class CameraController : public entities::Component
{
  struct Point
  {
    int x;
    int y;
  };

  engine::render::Camera* const m_camera;
  const ApplicationParam* const m_application;
  Point m_oldMousePos{};

public:
  CameraController(engine::render::Camera* const camera, const ApplicationParam* const appParam);

  void update(float dt) override;
};