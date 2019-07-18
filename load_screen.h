#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H

#include <QSplashScreen>
#include <QEvent>
#include <QWidget>
#include <QTimer>
#include <QEventLoop>

class LoadScreen : public QSplashScreen
{
public:
	LoadScreen(const QPixmap &pixmap = QPixmap(), QWidget *parent = nullptr);
	~LoadScreen();


protected:
	void mousePressEvent(QMouseEvent *) override;


private:
	QTimer _timer;
	QEventLoop _loop;
};
#endif

