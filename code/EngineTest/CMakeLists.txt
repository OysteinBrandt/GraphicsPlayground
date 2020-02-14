if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()
add_executable( EngineTest )

set( 
	SOURCE_FILES
		DebugToolsTest/ProfilerTest.cpp
		main.cpp
		Math/Mat2Test.cpp
		Math/Mat3Test.cpp
		Math/Mat4Test.cpp
		Math/MathTestHelper.h
		Math/Vec2Test.cpp
		Math/Vec3Test.cpp
)

set( TEST_API_SOURCE_FILES
	${ROOT_DIR}/../3rdParty/gtest/src/gtest-all.cc
)

target_sources( EngineTest PRIVATE ${SOURCE_FILES} ${TEST_API_SOURCE_FILES} )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "src" FILES ${SOURCE_FILES} )
source_group( "test-api" FILES ${TEST_API_SOURCE_FILES} )

target_include_directories( EngineTest PRIVATE ${ROOT_DIR} )
target_include_directories( EngineTest PRIVATE ${ROOT_DIR}/../3rdParty/gtest/ )

target_link_libraries( EngineTest PRIVATE Engine )

target_compile_definitions( EngineTest PRIVATE ENGINE_DLL=1 )

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
	target_compile_options( EngineTest  PRIVATE -Wall -Wextra -Wunreachable-code )
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( EngineTest  PRIVATE /W4 )	# TODO: Enable /WX (treat warnings as errors)
else()
	message(SEND_ERROR "'" ${CMAKE_CXX_COMPILER_ID} "' is not a supported compiler!")
endif()

target_compile_features( EngineTest
	PRIVATE
		cxx_std_17
)
