#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class QLabel;
class QPushButton;

class About : public QDialog
{
	Q_OBJECT

public:
	About();
	~About();

private:
	QPushButton *button;
	QLabel *textAbout;
};

#endif


