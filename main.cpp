#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <main_window.h>
#include "load_screen.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QPixmap pixel(":/pic/logo.png");
	LoadScreen loadScreen(pixel);
	loadScreen.show();

	MainWindow widget;

	QEventLoop loop;
	QTimer::singleShot(3000, &loop, &QEventLoop::quit);
	loop.exec();
	
	loadScreen.finish(&widget);
	widget.show();
	
	return app.exec();
}