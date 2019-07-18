#include <QApplication>
#include <main_window.h>
#include "load_screen.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow widget;
	QPixmap pixel(":/pic/logo.png");
	LoadScreen loadScreen(pixel);
	loadScreen.show();
	
	
	loadScreen.finish(&widget);
	widget.show();
	
	return app.exec();
}