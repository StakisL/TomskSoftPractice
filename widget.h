#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include "currency.h"

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;

/*
    Класс описывает основную форму и ее компоненты.
*/

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

public slots:
	void createWindow();
	void doConvert();

private:
	void createGridGroupBox();
	void createFormGroupBox();

	enum { NumGridRows = 5};

	QPushButton *aboutButton;
	QPushButton *submitButton;

	QGroupBox *gridGroupBox;
	QGroupBox *formGroupBox;

	QLabel *currencyCollums[NumGridRows];
	QLabel *valueCollums[NumGridRows];
	QLabel *valueLabel;
	QLabel *currencyLabel;

	QLineEdit *valueEdit;
	QComboBox *currencyBox;

	QVector<Currency*> currencyWired;

};

#endif