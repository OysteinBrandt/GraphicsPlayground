#pragma once

#include "Entities/Component.h"

namespace engine::render { class Renderable; }
namespace math { class Vec3; }

namespace entities::component
{
	class OBR_API Positional : public Component
	{
		engine::render::Renderable *m_renderable;

	public:
		void assign(engine::render::Renderable *renderable);
		void update(float) override;
		void position(const math::Vec3 &pos);
	};
}