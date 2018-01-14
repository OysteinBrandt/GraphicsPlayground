#pragma once

#include "Engine/Entities/Component.h"
#include "Engine/Math/Vec3.h"
#include <vector>

namespace entities::component
{
	class Physics;
	class OBR_API Lerp : public Component
	{
		Physics &m_physics;
		const std::vector<math::Vec3> &m_points;
		float m_alpha;
		size_t m_source;
		size_t m_destination;

	public:
		Lerp(const std::vector<math::Vec3> &lerpPoints, Physics &physics);

		void update(float dt) override;

	private:

		void targetNextLerpPoints();
	};
}