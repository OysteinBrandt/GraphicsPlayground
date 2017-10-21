#include "CustomMainWindow.h"

CustomMainWindow::CustomMainWindow()
{
	setLayout(&mainLayout);
	mainLayout.addLayout(&controlsLayout);
	mainLayout.addWidget(&oglWindow);

	controlsLayout.addLayout(&sliderLayout);
	sliderLayout.addWidget(&slider);
	sliderLayout.addWidget(&slider2);
	sliderLayout.addWidget(&slider3);
}


CustomMainWindow::~CustomMainWindow()
{
}
