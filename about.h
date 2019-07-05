#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class QLabel;
class QPushButton;

class About : public QDialog
{
	Q_OBJECT

public:
	About(QDialog *parent = 0);
	~About();

private:
	QPushButton *button;
	QLabel *textAbout;
};

#endif


