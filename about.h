#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class QLabel;
class QPushButton;

/*
    Класс описывает форму About
*/
class About : public QDialog
{
	Q_OBJECT

public:
	explicit About(QDialog *parent = 0);
	~About();

private:
	QPushButton *button;
	QLabel *textAbout;
};

#endif


