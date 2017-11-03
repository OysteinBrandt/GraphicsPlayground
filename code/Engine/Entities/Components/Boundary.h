#pragma once

#include "Entities/Component.h"
#include "Math/Vec3.h"
#include <vector>

namespace entities::component
{
	class Physics;
	class OBR_API Boundary : public Component
	{
		Physics &m_physics;
		math::Vec3 prevFramePos;
		const std::vector<math::Vec3> &m_boundary;
		
	public:
		Boundary(Physics &physicsComp, const std::vector<math::Vec3> &boundary);
		void update(float dt) override;

	};
}
