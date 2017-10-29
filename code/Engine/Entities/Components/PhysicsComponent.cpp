#include "PhysicsComponent.h"
#include "Entities/Entity.h"

namespace entities::component
{

	void PhysicsComponent::update(/*deltaTime*/)
	{
		velocity += acceleration;
		getParent()->position += velocity;
		getParent()->orientation += angularVelocity;
	}

}