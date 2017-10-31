#pragma once

#include "Entities/Component.h"
#include "Math/Vec3.h"
#include <vector>

namespace entities::component
{
	class PhysicsComponent;
	class OBR_API BoundaryHandlerComponent : public Component
	{
		PhysicsComponent &m_physics;
		math::Vec3 prevFramePos;
		const std::vector<math::Vec3> &m_boundary;
		
	public:
		BoundaryHandlerComponent(PhysicsComponent &physicsComp, const std::vector<math::Vec3> &boundary);
		void update(float dt) override;

	};
}
