#include "LerpComponent.h"
#include "Entities/Entity.h"

#include <cassert> // TODO: Assert rewrite

namespace entities::component
{

	LerpComponent::LerpComponent(const std::vector<math::Vec3>& lerpPoints, Physics & physics)
		: m_physics(physics), m_points(lerpPoints), m_source(0), m_destination(1)
	{
		//assert(m_points.size() >= 2);	// TODO: reference to points is updated after construction
	}

	void LerpComponent::update(float dt)
	{
		m_alpha += dt;
		if (m_alpha >= 1.0f)
		{
			m_alpha = 0.0f;
			targetNextLerpPoints();
		}
		const math::Vec3& source = m_points.at(m_source);
		const math::Vec3& dest = m_points.at(m_destination);
		getParent()->position = math::lerp(m_alpha, source, dest);
	}

	void LerpComponent::targetNextLerpPoints()
	{
		m_source = m_destination;
		m_destination = (m_destination + 1) % m_points.size();
	}

}