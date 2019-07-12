#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
<<<<<<< HEAD
#include <main_window.h>
=======
#include <widget.h>
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
<<<<<<< HEAD
	MainWindow widget;
=======
	mainWindow widget;
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
	widget.show();

	return app.exec();
}