#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include <QSplashScreen>
#include <QEvent>
#include <QWidget>
#include <QTimer>
#include "main_window.h"

class LoadScreen : public QSplashScreen
{
public:
	LoadScreen(MainWindow *main, const QPixmap &pixmap = QPixmap(), QWidget *parent = nullptr);
	~LoadScreen();

private:
	void quit();

protected:
	void mousePressEvent(QMouseEvent *) override;


private:
	QTimer _timer;
	MainWindow *_mainWindow;
};
#endif

