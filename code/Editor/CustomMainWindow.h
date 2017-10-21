#pragma once
#include <QtWidgets/qwidget.h>

// TODO: Move to CPP?
#include "OpenGLWindow.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qslider.h>

class CustomMainWindow : public QWidget
{
private:
	QVBoxLayout mainLayout;
	QVBoxLayout controlsLayout;
	OpenGLWindow oglWindow;

	QHBoxLayout sliderLayout;
	QSlider slider;
	QSlider slider2;
	QSlider slider3;

public:
	CustomMainWindow();
	~CustomMainWindow();
};

