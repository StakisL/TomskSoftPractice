<<<<<<< HEAD:main_window.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QVector>
#include <QLayout>
#include "currency.h"
#include "parse.h"

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;

/*
    Êëàññ îïèñûâàåò îñíîâíóþ ôîðìó è åå êîìïîíåíòû.
*/

class mainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit mainWindow(QWidget *parent = 0);
	~mainWindow();

public slots:
	void createWindow();
	void doConvert();
	void onReplyAccept();


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
	RequestAPI *parserRequest;
};

#endif
=======
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QVector>
#include <QLayout>
#include "currency.h"
#include "parse.h"

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;

/*
    Êëàññ îïèñûâàåò îñíîâíóþ ôîðìó è åå êîìïîíåíòû.
*/

class mainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit mainWindow(QWidget *parent = 0);
	~mainWindow();

public slots:
	void createWindow();
	void doConvert();
	void onReplyAccept();


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
	RequestAPI *parserRequest;
};

#endif
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b:main_window.h
