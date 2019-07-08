#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <widget.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Widget widget;
	widget.show();

	return app.exec();
}