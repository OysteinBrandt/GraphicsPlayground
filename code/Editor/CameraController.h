#pragma once

#include <Engine/Entities/Component.h>
#include <Engine/Math/Trigonometric.h>

namespace engine::render { class Camera; }
namespace details { struct Window; }
struct ApplicationParam;

class CameraController : public entities::Component
{
  engine::render::Camera* const m_camera;
  const ApplicationParam& m_application;

  math::Degrees m_yaw{ -90.f };
  math::Degrees m_pitch{ 0.f };

public:
  CameraController(engine::render::Camera* const camera, const ApplicationParam& appParam);

  void update(float dt) override;
};