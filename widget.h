#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

private slots:
	void createWindow();
	//void sendData();

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


};

#endif