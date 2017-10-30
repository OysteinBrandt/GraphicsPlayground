#pragma once

#include "Entities/Component.h"

namespace engine::render { class Renderable; }

namespace entities::component
{
	class OBR_API RendererComponent : public Component
	{
		engine::render::Renderable *m_renderable;

	public:
		void assign(engine::render::Renderable *renderable);

		void update(float) override;
	};
}