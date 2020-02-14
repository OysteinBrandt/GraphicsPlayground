add_library( Engine SHARED )

set(
	SOURCE_FILES
		Assert/AssertException.h
		Assert.cpp
		Assert.h
		DebugTools/DebugTools.h
		DebugTools/Profile.h
		DebugTools/Profiler.cpp
		DebugTools/Profiler.h
		DllHelper.h
		Engine.cpp
		Engine.h
		EngineException.h
		Entities/Component.h
		Entities/Components/Boundary.cpp
		Entities/Components/Boundary.h
		Entities/Components/Lerp.cpp
		Entities/Components/Lerp.h
		Entities/Components/Physics.cpp
		Entities/Components/Physics.h
		Entities/Components/Positional.cpp
		Entities/Components/Positional.h
		Entities/Entity.cpp
		Entities/Entity.h
		Generator/Cube.cpp
		Generator/Cube.h
		Generator/Shape.h
		Generator/Sphere.cpp
		Generator/Sphere.h
		Input/KeyInput.cpp
		Input/KeyInput.h
		Input/KeyMapperInterface.h
		Math/Constants.h
		Math/Mat2.cpp
		Math/Mat2.h
		Math/Mat3.cpp
		Math/Mat3.h
		Math/Mat4.cpp
		Math/Mat4.h
		Math/Trigonometric.h
		Math/Vec2.h
		Math/Vec3.cpp
		Math/Vec3.h
		Render/Camera.cpp
		Render/Camera.h
		Render/Color.h
		Render/OpenGL/OpenGLModel.cpp
		Render/OpenGL/OpenGLModel.h
		Render/OpenGL/Renderer.cpp
		Render/OpenGL/Renderer.h
		Render/OpenGL/Shader.cpp
		Render/OpenGL/Shader.h
		Render/OpenGL/Texture.cpp
		Render/OpenGL/Texture.h
		Render/Renderable.cpp
		Render/Renderable.h
		Render/RenderMode.h
		Utilities/stl_util.h
		Utilities/TypeTraits.h
)

target_sources( Engine PRIVATE ${SOURCE_FILES} )

source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "src" FILES ${SOURCE_FILES} )

target_include_directories( Engine PRIVATE ${ROOT_DIR} )

target_link_libraries( Engine opengl32 )

# TODO(obr): Make the include and linking PRIVATE and fix glew includes in code
target_link_libraries( Engine ${ROOT_DIR}/../3rdParty/glew/lib/Release/x64/glew32.lib )
target_include_directories( Engine PUBLIC ${ROOT_DIR}/../3rdParty/glew/include )

# TODO: Add $<CONFIG> to path if cmake configured for Visual Studio ?
#       Must figure out how to handle build config properly
add_custom_command(TARGET Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ROOT_DIR}/../3rdParty/glew/bin/Release/x64/glew32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

target_compile_definitions( Engine PRIVATE ENGINE_DEBUG=1 ENGINE_DLL=1 ENGINE_DLL_EXPORT=1 )

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
	target_compile_options( Engine  PRIVATE -Wall -Wextra -Wunreachable-code )
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( Engine  PRIVATE /W4 )	# TODO: Enable /WX (treat warnings as errors)
else()
	message(SEND_ERROR "'" ${CMAKE_CXX_COMPILER_ID} "' is not a supported compiler!")
endif()

target_compile_features( Engine
	PRIVATE
		cxx_std_17
)
