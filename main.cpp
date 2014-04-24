#include <QApplication>
#include "GUIWindow.h"

int main( int argc, char** argv )
{
	// QT Stuff
	QApplication app( argc, argv );

	GUIWindow win;
	win.show();

	return app.exec();
}