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

private slots:
	void update();
};

