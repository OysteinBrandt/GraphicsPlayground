#include "Positional.h"
#include "Rendering/Renderer.h"
#include "Entities/Entity.h"

namespace entities::component
{

void Positional::assign(engine::render::Renderer *renderer, size_t instance)
{
	m_renderer = renderer;
	m_instance = instance;
}

void Positional::update(float)
{
	auto *renderable = m_renderer->getRenderable(m_instance);
	renderable->m_matrix = math::Mat4::translate(getParent()->position) *
												 math::Mat4::rotate(getParent()->orientation, math::Mat4::Axis::Z);
}

void Positional::position(const math::Vec3 &pos)
{
	getParent()->position = pos;
}

}