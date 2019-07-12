#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVector>
#include <QLayout>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QLocale>
#include "currency.h"
#include "request_api.h"


class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;
class QFormLayout;
class QMenuBar;
/*
    Класс описывает основную форму и ее компоненты.
*/

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void createAboutWindow();
	void doConvert();
	void onReplyAccept();
	void setEnableButton();

	void createResultConvertBox();
	void createBaseCurrencyBox();

	QPushButton *_submitButton;

	QGroupBox *_gridGroupBox;
	QGroupBox *_formGroupBox;

	QVBoxLayout *_mainLayout;
	QFormLayout *_formLayout;
	QGridLayout *_gridLayout;
	QMenuBar *_about;

	QVector<QLabel*> _currencyCollums;
	QVector<QLabel*> _valueCollums;

	QLabel *_valueLabel;
	QLabel *_currencyLabel;

	QLineEdit *_valueEdit;
	QComboBox *_currencyBox;

	QVector<Currency*> _currencyWired;
	RequestAPI *_parserRequest;
};

#endif
