#include <QApplication>
#include "main_window.h"
#include "load_screen.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//MainWindow mainWindow;
	LoadScreen loadScreen(QPixmap(":/pic/logo.png"));
	
	//mainWindow.show();
	return app.exec();
}