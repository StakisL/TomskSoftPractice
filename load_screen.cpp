#include "load_screen.h"



LoadScreen::LoadScreen(const QPixmap &pixmap , QWidget *parent)
{
	this->setPixmap(pixmap);
}

void LoadScreen::mousePressEvent(QMouseEvent *mouse)
{
	QWidget::setEnabled(false);
}

LoadScreen::~LoadScreen()
{
}
