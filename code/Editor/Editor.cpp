#include "Editor.h"

#include "Engine/Assert.h"
#include <iostream>

// TODO: Make sure timer is correct in first frame (m_previousFrame)
//       There could be a large gap between initialization and update
Editor::Editor(const ApplicationParam &param)
  : m_previousFrame{ std::chrono::high_resolution_clock::now() }
{
  auto handler = [](const engine::Assert& assert)
  {
    std::cout << "=============================\n"
      << "Assert detected!" << "\n"
      << assert.what << "\n"
      << "function: " << assert.functionName << "\n"
      << "file: " << assert.fileName << " (" << assert.line << ")\n";
  };
  engine::assert::HandlerContainer::attach(handler);
  engine::init(engine::Renderer::OpenGL);

  m_camera = engine::render::Camera{ { 0.f, 0.f, 3.f } };
  m_cameraController = std::make_unique<CameraController>(&m_camera, param);

  engine::render::opengl::ShaderConfiguration sc;
  sc.vertexShader = "phong.vert";
  sc.fragmentShader = "phong.frag";
  sc.useCombinedMvpMatrix = false;
  sc.type = engine::render::opengl::ShaderType::PHONG;
  m_renderer = std::make_unique<engine::render::opengl::Renderer>(m_camera, engine::render::opengl::Shader(sc));
  //m_renderer = std::make_unique<engine::render::opengl::Renderer>(m_camera, engine::render::opengl::Shader({ "defaultVertex.vert", "defaultFragment.frag" }));
  //m_gameScene = std::make_unique<scenes::SimpleGame>(m_keyInput);
  m_cubeScene = std::make_unique<scenes::Cubes>(*m_renderer);
  //m_collisionScene = std::make_unique<scenes::Collision>(*m_renderer);
  frames = 0;
}

void Editor::update()
{
  auto current_frame = std::chrono::steady_clock::now();
  const std::chrono::duration<float> deltaTime = current_frame - m_previousFrame;
  m_previousFrame = current_frame;
  const auto dt = deltaTime.count();   // std::min(std::chrono::milliseconds(15), diff);

  //++frames;
  //if (frames % 100 == 0)
  //{
  //  std::cout << (1 / dt) << std::endl;
  //  frames = 0;
  //}

  m_cameraController->update(dt);
  m_camera.update();
  //m_gameScene->update(dt);
  m_cubeScene->update(dt);
  //m_collisionScene->update(dt);
}

void Editor::render(float width, float height)
{
  // TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
  m_camera.updateProjection(width, height);
  m_renderer->render();
  //m_gameScene->render(width, height);
}