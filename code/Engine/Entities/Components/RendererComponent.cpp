#include "RendererComponent.h"
#include "Rendering/Renderable.h"
#include "Entities/Entity.h"

namespace entities::component
{

void RendererComponent::assign(engine::render::Renderable *renderable)
{
	m_renderable = renderable;
}

void RendererComponent::update(float)
{
	m_renderable->m_matrix = math::Mat3::translate(getParent()->position) * math::Mat3::rotate(getParent()->orientation, math::Mat3::Axis::Z);
}

}