#include "Positional.h"
#include "Rendering/Renderable.h"
#include "Entities/Entity.h"

namespace entities::component
{

void Positional::assign(engine::render::Renderable *renderable)
{
	m_renderable = renderable;
}

void Positional::update(float)
{
	m_renderable->m_matrix = math::Mat4::translate(getParent()->position) * 
													 math::Mat4::rotate(getParent()->orientation, math::Mat4::Axis::Z);
}

void Positional::position(const math::Vec3 &pos)
{
	getParent()->position = pos;
}

}