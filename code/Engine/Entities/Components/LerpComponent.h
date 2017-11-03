#pragma once

#include "Entities/Component.h"
#include "Math/Vec3.h"
#include <vector>

namespace entities::component
{
	class Physics;
	class OBR_API LerpComponent : public Component
	{
		Physics &m_physics;
		const std::vector<math::Vec3> &m_points;
		float m_alpha;
		size_t m_source;
		size_t m_destination;

	public:
		LerpComponent(const std::vector<math::Vec3> &lerpPoints, Physics &physics);

		void update(float dt) override;

	private:

		void targetNextLerpPoints();
	};
}