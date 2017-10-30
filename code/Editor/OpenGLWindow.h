#pragma once

#include "Editor.h"
#include <QtWidgets/qopenglwidget.h>
#include <QtCore/qtimer.h>
#include <chrono>
#include <memory>
class QKeyEvent;

namespace math { class Vec3; }

class OpenGLWindow : public QOpenGLWidget
{
	Q_OBJECT

private:

	std::unique_ptr<Editor> m_editor;

	QTimer m_gameLoop;

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
	void handleBoundaries(std::vector<math::Vec3> &boundaries);

private slots:
	void update();
};

