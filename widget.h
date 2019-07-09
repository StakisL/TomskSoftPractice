#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QVector>
#include <QLayout>
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
	explicit Widget(QWidget *parent = 0);
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

	QVBoxLayout *mainLayout;
	QFormLayout *formLayout;
	QGridLayout *gridLayout;

	QLabel *currencyCollums[NumGridRows];
	QLabel *valueCollums[NumGridRows];
	QLabel *valueLabel;
	QLabel *currencyLabel;

	QLineEdit *valueEdit;
	QComboBox *currencyBox;

	QVector<Currency*> currencyWired;

};

#endif