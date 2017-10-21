#pragma once

#include <QtWidgets/qopenglwidget.h>
#include <QtCore/qtimer.h>
#include <chrono>

class QKeyEvent;

class OpenGLWindow : public QOpenGLWidget
{
	Q_OBJECT

private:

	GLuint m_vertexBufferId;
	GLuint m_indexBufferId;
	QTimer m_gameLoop;
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;

public:
	OpenGLWindow();

protected:
	void initializeGL() override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);

private:
	bool checkShaderStatus(GLuint shaderId) const;
	bool checkProgramStatus(GLuint programId) const;
	std::string readShaderCode(const std::string &fileName) const;
	void installShaders();

private slots:
	void update();
};

