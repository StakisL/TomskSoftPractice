#include "load_screen.h"



LoadScreen::LoadScreen(const QPixmap &pixmap , QWidget *parent)
{
	this->setPixmap(pixmap);
	this->show();
	
	_timer.singleShot(3000, &_loop, &QEventLoop::quit);
	_loop.exec();
}

void LoadScreen::mousePressEvent(QMouseEvent *mouse)
{
	_loop.exit();
	_timer.stop();
}

LoadScreen::~LoadScreen()
{
}
