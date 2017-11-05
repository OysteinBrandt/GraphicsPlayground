#include <QtGui/qevent.h>

#include "OpenGLWindow.h"
#include "Editor.h"

#include <iostream>


OpenGLWindow::OpenGLWindow()
{
	setFocusPolicy(Qt::StrongFocus);
	setMinimumSize(1200, 600);
}

void OpenGLWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	if (errorCode != 0)
		std::cout << "Failed to initialize glew!" << std::endl;

	try
	{
		m_editor = std::make_unique<Editor>();

		connect(&m_gameLoop, SIGNAL(timeout()), this, SLOT(update()));
		m_gameLoop.start();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught during initialization!" << e.what() << std::endl;
	}
}

void OpenGLWindow::paintGL()
{
	try
	{
		m_editor->update();
		m_editor->render(width(), height());
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught during update/render loop!" << e.what() << std::endl;
		std::cin.get();
	}
}

void OpenGLWindow::update()
{
	repaint();
}