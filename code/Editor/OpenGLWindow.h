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

	GLuint m_boundariesVertBufferId;
	GLuint m_boundariesIndexBufferId;

	QTimer m_gameLoop;
	std::chrono::time_point<std::chrono::steady_clock> m_frameTimer;

public:
	OpenGLWindow();

protected:
	void initializeGL() override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void processKeyToggle(int key, bool enabled);

private:
	bool checkShaderStatus(GLuint shaderId) const;
	bool checkProgramStatus(GLuint programId) const;
	std::string readShaderCode(const std::string &fileName) const;
	void installShaders();
	void handleBoundaries();

private slots:
	void update();
};

