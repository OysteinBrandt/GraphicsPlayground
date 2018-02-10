#pragma once

#include "ApplicationParam.h"
#include <Engine/Engine.h>
#include "CameraController.h"
#include "Scenes/SimpleGame.h"
#include "Scenes/Cubes.hpp"
#include "Scenes/Collision.h"
#include <Engine/Render/OpenGL/Renderer.h>
#include <Engine/Render/Camera.h>

#include <memory>
#include <chrono>

class Editor
{
  std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;
  std::unique_ptr<CameraController> m_cameraController;

  engine::render::Camera m_camera;

  std::unique_ptr<engine::render::opengl::Renderer> m_renderer;
  //std::unique_ptr<scenes::SimpleGame> m_gameScene;
  //std::unique_ptr<scenes::Cubes> m_cubeScene;
  std::unique_ptr<scenes::Collision> m_collisionScene;
  int frames;

public:
  Editor(const ApplicationParam &param);

  void update();
  void render(float width, float height);

};

