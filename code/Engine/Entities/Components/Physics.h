#pragma once

#include "Engine/Entities/Component.h"
#include "Engine/Math/Vec3.h"

namespace entities::component
{
	class OBR_API Physics : public Component
	{
	public:
		math::Vec3 velocity;
		math::Vec3 acceleration;
		float angularVelocity;
		
		Physics() : angularVelocity{0.0f}
		{ }

		void update(float dt) override;
	};
}