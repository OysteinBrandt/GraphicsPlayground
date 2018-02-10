#include "Editor.h"

#include <iostream>

// TODO: Make sure timer is correct in first frame (m_frameTimer)
Editor::Editor(const ApplicationParam &param)
  : m_frameTimer{ std::chrono::high_resolution_clock::now() }
{
  engine::init(engine::Renderer::OpenGL);

  m_camera = engine::render::Camera{ { 0.f, 0.f, -3.f } };
  m_cameraController = std::make_unique<CameraController>(&m_camera, &param);

  m_renderer = std::make_unique<engine::render::opengl::Renderer>(m_camera, engine::render::opengl::Shader("defaultVertex.vert", "defaulFragment.frag"));
  //m_gameScene = std::make_unique<scenes::SimpleGame>(m_keyInput);
  //m_cubeScene = std::make_unique<scenes::Cubes>(*m_renderer);
  m_collisionScene = std::make_unique<scenes::Collision>(*m_renderer);
  frames = 0;
}

void Editor::update()
{
  auto now = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<float> deltaTime = now - m_frameTimer;
  m_frameTimer = now;
  const auto dt = deltaTime.count();

  //++frames;
  //if (frames % 100 == 0)
  //{
  //  std::cout << (1 / dt) << std::endl;
  //  frames = 0;
  //}

  m_cameraController->update(dt);
  m_camera.update();
  //m_gameScene->update(dt);
  //m_cubeScene->update(dt);
  m_collisionScene->update(dt);
}

void Editor::render(float width, float height)
{
  // TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
  m_camera.updateProjection(width, height);
  m_renderer->render();
  //m_gameScene->render(width, height);
}