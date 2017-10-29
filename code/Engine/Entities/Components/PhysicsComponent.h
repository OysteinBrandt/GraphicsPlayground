#pragma once

#include "Entities/Component.h"
#include "Math/Vec3.h"

namespace entities::component
{
	class OBR_API PhysicsComponent : public Component
	{
	public:
		math::Vec3 velocity;
		math::Vec3 acceleration;
		float angularVelocity;
		
		PhysicsComponent() : angularVelocity{0.0f}
		{ }

		void update() override;
	};
}