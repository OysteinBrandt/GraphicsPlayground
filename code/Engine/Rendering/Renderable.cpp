#include "Renderable.h"
#include "Shader.h"

bool engine::render::Renderable::useProgram() const
{
	if (m_shader == nullptr)
		return false;
	
	m_shader->useProgram();
	return true;
}
