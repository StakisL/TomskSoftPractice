#include "load_screen.h"



LoadScreen::LoadScreen(MainWindow *main, const QPixmap &pixmap, QWidget *parent)
	: QSplashScreen(parent, pixmap)
	, _mainWindow(main)
{
	setPixmap(pixmap);
	show();
	
	if (pixmap.isNull())
	{
		finish(_mainWindow);
		_mainWindow->show();
	}
	else
	{
	    _timer.singleShot(3000, this, &LoadScreen::quit);
	}

}

void LoadScreen::quit()
{
	finish(_mainWindow);
	_mainWindow->show();
}

void LoadScreen::mousePressEvent(QMouseEvent *mouse)
{
	_timer.stop();
	quit();
}

LoadScreen::~LoadScreen() = default;
