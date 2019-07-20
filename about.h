#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QtWidgets>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class QLabel;
class QPushButton;

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



