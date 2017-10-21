#include <QtWidgets/qapplication.h>
#include "CustomMainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	CustomMainWindow window;
	window.show();

	return app.exec();
}