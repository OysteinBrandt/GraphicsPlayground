#include "Engine.h"

#include <GL/glew.h>
#include "Engine/Assert/AssertException.h"

namespace obr
{

Engine::Engine()
{
	GLenum errorCode = glewInit();
	ENGINE_ASSERT_EXCEPTION_IF(errorCode != GLEW_NO_ERROR, "Failed to initialize glew.");
}


Engine::~Engine()
{
}

void Engine::update()
{

}

void Engine::render()
{

}

}