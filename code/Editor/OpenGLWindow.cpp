#include <QtGui/qevent.h>

#include "OpenGLWindow.h"
#include "Editor.h"
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

	math::Vec3 position;
	math::Vec3 oldPosition;
	math::Vec3 velocity;
	const math::Vec3 dir(0, 1);
	const float acceleration{ 0.2f };
	float orientation{ 0.f };

	bool moveForwardToggle{ false };
	bool moveBackwardToggle{ false };
	bool rotateRightToggle{ false };
	bool rotateLeftToggle{ false };

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
	setFocusPolicy(Qt::StrongFocus);
	setMinimumSize(1200, 600);
}

void OpenGLWindow::initializeGL()
{
	try
	{
		m_editor = std::make_unique<Editor>();

		// Center OpenGL Viewport
		//int minViewportSize = std::min(width(), height());
		//math::Vec2 viewPortLocation;
		//viewPortLocation.x = width() / 2 - minViewportSize / 2;
		//viewPortLocation.y = height() / 2 - minViewportSize / 2;
		//glViewport(0, 0, viewPortLocation.x, viewPortLocation.y);

		//glEnable(GL_DEPTH_TEST);

		//installShaders();

		connect(&m_gameLoop, SIGNAL(timeout()), this, SLOT(update()));
		m_gameLoop.start();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught during initialization: " << e.what() << std::endl;
	}
}

void OpenGLWindow::paintGL()
{
	try
	{
		//static int frameStopper{ 1 };
		//if (frameStopper++ % 30 == 0)
		//	for (int i = 0; i < 20000; ++i)
		//		std::cout << "awd";

		m_editor->update();
		m_editor->render(width(), height());

		//handleBoundaries();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught during update/render loop: " << e.what() << std::endl;
		std::cin.get();
	}
}

void OpenGLWindow::keyPressEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	processKeyToggle(e->key(), true);
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	processKeyToggle(e->key(), false);
}

void OpenGLWindow::processKeyToggle(int key, bool enabled)
{
	switch (key)
	{
	case Qt::Key_W:
		moveForwardToggle = enabled;
		break;

	case Qt::Key_D:
		rotateRightToggle = enabled;
		break;

	case Qt::Key_A:
		rotateLeftToggle = enabled;
		break;

	case Qt::Key_S:
		moveBackwardToggle = enabled;
		break;

	default:
		break;
	}
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

void OpenGLWindow::handleBoundaries(std::vector<math::Vec3> &boundaries)
{
	bool collision{ false };
	for (size_t i = 0; i < boundaries.size(); ++i)
	{
		const auto &first = boundaries[i];
		const auto &second = boundaries[(i + 1) % boundaries.size()];

		const auto wall = second - first;
		const auto wallNormal = wall.perpCCW(); //.normalized();
		const auto respectivePosition = position - first;
		const float dotResult = wallNormal.dot(respectivePosition);

		collision = (dotResult < 0);

		if (collision)
		{
			velocity -= 2 * velocity.projectOnto(wallNormal);
			position = oldPosition;
		}
	}
}

void OpenGLWindow::update()
{
	repaint();
}