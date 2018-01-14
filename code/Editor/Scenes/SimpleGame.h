#pragma once

#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Shader.h>
#include <Engine/Rendering/Camera.h>
#include <Engine/Entities/Entity.h>
#include <Engine/Entities/Components/Positional.h>
#include <Engine/Entities/Components/Physics.h>
#include <Engine/Entities/Components/Boundary.h>
#include <Engine/Entities/Components/Lerp.h>
//#include "CameraController.h"
#include "ControllerComponent.h"

namespace engine::render { class Renderable; }
namespace input { class KeyInput; }

namespace scenes
{

	class SimpleGame
	{
#if 0
		engine::render::Camera m_camera;

		entities::Entity m_ship;
		entities::Entity m_lerper;

		std::vector<math::Vec3> m_boundaryVertices;
		std::vector<GLushort> m_boundaryIndices;
		std::vector<math::Vec3> m_lerpPoints;

		entities::component::Physics m_shipPhysics;
		entities::component::Boundary m_shipBoundaryHandler;
		engine::render::Renderer m_renderer;
		engine::render::Shader m_shader;
		engine::render::Renderable *m_shipRenderable;
		engine::render::Renderable *m_lerpRenderable;
		entities::component::Positional m_shipTransform;
		entities::component::Positional m_lerpTransform;
		entities::component::Lerp m_lerpLerper;

		//CameraController m_cameraController;
		ControllerComponent m_shipController;
	public:
		SimpleGame(const input::KeyInput &keyInput);

		void update(float dt);
		void render(float width, float height);

	private:

		void addShips();
		void addLerper(engine::render::OpenGLModel *model);
		void addBoundaries();
#endif
	};

}