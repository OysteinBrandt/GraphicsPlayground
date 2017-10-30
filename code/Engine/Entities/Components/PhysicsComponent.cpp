#include "PhysicsComponent.h"
#include "Entities/Entity.h"

namespace entities::component
{

	void PhysicsComponent::update(float dt)
	{
		velocity += acceleration * dt;
		getParent()->position += velocity * dt;
		getParent()->orientation += angularVelocity;
		acceleration = math::Vec3{};
	}

}