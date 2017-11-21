#pragma once

#include "Entities/Component.h"

namespace engine::render { class Renderer; }
namespace math { class Vec3; }

namespace entities::component
{
	class OBR_API Positional : public Component
	{
		engine::render::Renderer *m_renderer;
		size_t m_instance;

	public:
		void assign(engine::render::Renderer *renderer, size_t instance);
		void update(float) override;
		void position(const math::Vec3 &pos);
	};
}