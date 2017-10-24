#include <GL/glew.h>
#include <QtGui/qevent.h>

#include "OpenGLWindow.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Mat3.h"
#include "DebugTools/Profile.h"

// TODO: Refactor
#include <cassert>
#include <fstream>

// TODO: Remove
#include <iostream>

#include <array>

namespace {
	std::array<math::Vec3, 6> verts
	{
		math::Vec3(+0.0f, +0.14142135623f, -1),
		math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(-0.1f, -0.1f, -1),
		math::Vec3(+1.0f, +0.0f, 0.0f),

		math::Vec3(+0.1f, -0.1f, -1),
		math::Vec3(+1.0f, +0.0f, 0.0f)


		//math::Vec3(-1.0f, +1.0f, -0.5f),
		//math::Vec3(+0.0f, +1.0f, 0.0f),

		//math::Vec3(+0.0f, -1.0f, -0.5f),
		//math::Vec3(+0.0f, +1.0f, 0.0f),

		//math::Vec3(+1.0f, +1.0f, -0.5f),
		//math::Vec3(+0.0f, +1.0f, 0.0f),
	};

	math::Vec3 position(-0.5f, -0.5f);

	bool checkStatus(
		GLuint objectId,
		PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		GLenum statusType)
	{
		GLint status;
		objectPropertyGetterFunc(objectId, statusType, &status);
		if (status != GL_TRUE)
		{
			GLint infoLogLength;
			objectPropertyGetterFunc(objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLsizei bufferSize;
			std::string log;
			log.reserve(infoLogLength);
			getInfoLogFunc(objectId, infoLogLength, &bufferSize, &log[0]);
			std::cout << log.c_str() << std::endl;
			return false;
		}
		return true;
	}
}

OpenGLWindow::OpenGLWindow()
{
	setMinimumSize(1200, 600);
}

void OpenGLWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);

	// Center OpenGL Viewport
	//int minViewportSize = std::min(width(), height());
	//math::Vec2 viewPortLocation;
	//viewPortLocation.x = width() / 2 - minViewportSize / 2;
	//viewPortLocation.y = height() / 2 - minViewportSize / 2;
	//glViewport(0, 0, viewPortLocation.x, viewPortLocation.y);

	glEnable(GL_DEPTH_TEST);

	//----------------------------------------------------------------------------------------

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts.data(), /*GL_STATIC_DRAW*/GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vec3)*2, nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vec3)*2, (char*)(sizeof(math::Vec3)));


	//GLushort indices[] = {0, 1, 2/*,  3,4,5*/};
	//glGenBuffers(1, &m_indexBufferId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	errorCode = glGetError();
	assert(errorCode == 0);

	installShaders();

	//----------------------------------------------------------------------------------------

	connect(&m_gameLoop, SIGNAL(timeout()), this, SLOT(update()));
	m_frameTimer = std::chrono::high_resolution_clock::now();
	m_gameLoop.start();
}

static float orientation{ 0 };
void OpenGLWindow::paintGL()
{
	NEW_PROFILING_FRAME();

	// Update
	auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> deltaT = now - m_frameTimer;
	const float delta = deltaT.count();
	m_frameTimer = now;

	//static int counter{ 0 };
	//++counter;
	//if (counter % 10000 == 0)
	//{
	//	std::cout << "delta time: " << delta << std::endl;
	//	std::cout << "Fps: " << 1.0f / delta << std::endl;
	//	std::cout << "-------------------" << std::endl;
	//}

	//static int frameStopper{ 1 };
	//if (frameStopper++ % 30 == 0)
	//	for (int i = 0; i < 20000; ++i)
	//		std::cout << "awd";

	math::Vec3 upVector(0, 1);
	auto op = math::Mat3::rotate(orientation, math::Mat3::Axis::Z);
	auto directionToAccel = op * upVector;
	const float acceleration{ 0.2f };

	position += directionToAccel * acceleration * delta;

	//-------------------------------------------------------------------

	// Render
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	orientation += 0.0005f;
	math::Mat3 matrix;
	{
		PROFILE("Matrix Multiplication");
		matrix = math::Mat3::translate(math::Vec2(position.x, position.y)) *
			math::Mat3::rotate(orientation, math::Mat3::Axis::Z);
	}

	std::array<math::Vec3, 6> translatedVerts;
	{
		PROFILE("Vector Transformation");
		for (size_t i = 0; i < verts.size(); ++i)
		{
			if (i % 2 == 0)
			{
				translatedVerts[i] = matrix * verts[i];
			}
			else
				translatedVerts[i] = verts[i];
		}
	}

	// Replace buffer with new vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(translatedVerts), translatedVerts.data());

	// Draw directly
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Draw with indices
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
}

void OpenGLWindow::keyPressEvent(QKeyEvent* e)
{
	const float speed = 0.02f;
	if (e->key() == Qt::Key_Up)
		position.y += speed;
	if (e->key() == Qt::Key_Down)
		position.y -= speed;
	if (e->key() == Qt::Key_Right)
		position.x += speed;
	if (e->key() == Qt::Key_Left)
		position.x -= speed;
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent*)
{

}

bool OpenGLWindow::checkShaderStatus(GLuint shaderId) const
{
	return checkStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool OpenGLWindow::checkProgramStatus(GLuint programId) const
{
	return checkStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string OpenGLWindow::readShaderCode(const std::string &fileName) const
{
	std::ifstream stream("D:/src/GraphicsPlayground/Resources/Shaders/" + fileName);
	if (!stream.good())
	{
		std::cout << "Failed to load shader: " + fileName << std::endl;
		return {};
	}

	return std::string(
		(std::istreambuf_iterator<char>(stream)), 
		std::istreambuf_iterator<char>());
}

void OpenGLWindow::installShaders()
{
	/*
	struct StringHelper {
		const char *p;
		StringHelper(const std::string& s) : p(s.c_str()) {}
		operator const char**() { return &p; }
	};
	*/

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShader = readShaderCode("defaultVertex.vert");
	const char *vertShader = vertexShader.c_str();
	glShaderSource(vertexShaderId, 1, &vertShader, nullptr);

	std::string fragmentShader = readShaderCode("defaulFragment.frag");
	const char *fragShader = fragmentShader.c_str();
	glShaderSource(fragmentShaderId, 1, &fragShader, nullptr);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	if (!checkShaderStatus(vertexShaderId) || !checkShaderStatus(fragmentShaderId))
		return;

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// TODO: Find out why checkProgramStatus does not cout errors
	if (!checkProgramStatus(programId))
		return;

	glUseProgram(programId);
}

void OpenGLWindow::update()
{
	repaint();
}