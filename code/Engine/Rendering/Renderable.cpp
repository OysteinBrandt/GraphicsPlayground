#include "Renderable.h"
#include "Shader.h"

namespace engine::render
{

	const Shader* Renderable::shader() const
	{
		return m_customShader;
	}

}