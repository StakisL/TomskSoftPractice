#include <QApplication>
#include "main_window.h"
#include "load_screen.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	LoadScreen loadScreen(QPixmap(":/pic/logo.png"));
	return app.exec();
}