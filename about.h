#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLayout>
#include <QtWidgets>

class QLabel;
class QPushButton;

/*
    Класс описывает форму About
*/
class About : public QDialog
{
	Q_OBJECT

public:
	explicit About(QDialog *parent = nullptr);
	~About();

private:
	QPushButton *_button;
	QLabel *_textAbout;
	QVBoxLayout *_mainLayout;
};

#endif



