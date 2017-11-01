#include "BoundaryHandlerComponent.h"
#include "Entities/Entity.h"
#include "Entities/Components/PhysicsComponent.h"

namespace entities::component
{

	BoundaryHandlerComponent::BoundaryHandlerComponent(PhysicsComponent &physicsComp, const std::vector<math::Vec3>& boundary)
		: m_physics(physicsComp), m_boundary(boundary)
	{
	}

	void BoundaryHandlerComponent::update(float dt)
	{
		bool collision{ false };
		for (size_t i = 0; i < m_boundary.size(); ++i)
		{
			const auto &first = m_boundary.at(i);
			const auto &second = m_boundary.at( (i + 1) % m_boundary.size() );

			const auto wall = second - first;
			const auto wallNormal = wall.perpCCW(); //.normalized();
			const auto respectivePosition = getParent()->position - first;
			const auto dotResult = wallNormal.dot(respectivePosition);

			collision = (dotResult < 0);
			if (collision)
			{
				m_physics.velocity -= 2 * m_physics.velocity.projectOnto(wallNormal);
				getParent()->position = prevFramePos;
			}
			prevFramePos = getParent()->position;
		}
	}

}