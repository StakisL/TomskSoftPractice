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
<<<<<<< HEAD
<<<<<<< HEAD
	explicit About(QDialog *parent = nullptr);
	~About();

private:
	QPushButton *_button;
	QLabel *_textAbout;
	QVBoxLayout *_mainLayout;
=======
=======
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
	explicit About(QDialog *parent = 0);
	~About();

private:
	QPushButton *button;
	QLabel *textAbout;
	QVBoxLayout *mainLayout;
<<<<<<< HEAD
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
=======
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
};

#endif



