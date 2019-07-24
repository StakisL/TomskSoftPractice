#include <QApplication>
#include "main_window.h"
#include "load_screen.h"

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	MainWindow *mainWindow = new MainWindow();
	LoadScreen loadScreen(mainWindow, QPixmap(":/pic/logo.png"));

	auto result = app.exec();
	delete mainWindow;
	return result;
}