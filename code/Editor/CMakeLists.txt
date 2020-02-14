if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") # /ENTRY:mainCRTStartup
endif()

file( GLOB_RECURSE RESOURCE_FILES ${ROOT_DIR}/../Resources/*.*)

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
	message(SEND_ERROR "'" ${CMAKE_CXX_COMPILER_ID} "' is not a supported compiler!")
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	add_executable( Editor WIN32 win32_Editor.cpp )
else()
	message(SEND_ERROR "'" ${CMAKE_CXX_COMPILER_ID} "' is not a supported compiler!")
endif()

set(
	SOURCE_FILES
		ApplicationParam.h
		CameraController.h
		ControllerComponent.h
		Editor.h
		IORedirect.h
		ShapeController.h
		Scenes/Collision.h
		Scenes/Cubes.hpp
		Scenes/SimpleGame.h
		CameraController.cpp
		ControllerComponent.cpp
		Editor.cpp
		IORedirect.cpp
		ShapeController.cpp
		win32_Editor.cpp
		Scenes/Collision.cpp
		Scenes/Cubes.cpp
		Scenes/SimpleGame.cpp
)

target_sources( Editor PRIVATE ${SOURCE_FILES})

# *** Folders/Grouping for IDE project ********************************************************
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "src" FILES ${SOURCE_FILES} )

source_group( TREE ${ROOT_DIR}/../Resources/ PREFIX "resources" FILES ${RESOURCE_FILES} )
set_target_properties( Editor PROPERTIES RESOURCE "${RESOURCE_FILES}" )

# *********************************************************************************************

# TODO: Add $<CONFIG> to path if cmake configured for Visual Studio ?
#       Must figure out how to handle build config properly
set( BIN_RESOURCE_FOLDER_CONFIG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources/)

# Note: Must trigger a build for this command to take effect
add_custom_command(TARGET Editor PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_RESOURCE_FOLDER_CONFIG}
)

# Note: Must trigger a build for this command to take effect
add_custom_command(TARGET Editor PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RESOURCE_FILES} ${BIN_RESOURCE_FOLDER_CONFIG}
)

# TODO: Add $<CONFIG> to path if cmake configured for Visual Studio ?
#       Must figure out how to handle build config properly
set_property(TARGET Editor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# *********************************************************************************************

target_include_directories( Editor PRIVATE ${ROOT_DIR} )

target_link_libraries( Editor PRIVATE Engine )

target_compile_definitions( Editor PRIVATE ENGINE_DEBUG=1 ENGINE_DLL=1 )

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
	target_compile_options( Editor  PRIVATE -Wall -Wextra -Wunreachable-code )
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( Editor  PRIVATE /W4 )	# TODO: Enable /WX (treat warnings as errors)
else()
	message(SEND_ERROR "'" ${CMAKE_CXX_COMPILER_ID} "' is not a supported compiler!")
endif()

target_compile_features( Editor
	PRIVATE
		cxx_std_17
)
