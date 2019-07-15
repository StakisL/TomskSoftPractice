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
class QDateEdit;

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
	void selectDate(const QDate &date);

	void createResultConvertBox();
	void createBaseCurrencyBox();

	QDateEdit *_calendar;

	QPushButton *_submitButton;

	QGroupBox *_gridGroupBox;
	QGroupBox *_formGroupBox;

	QVBoxLayout *_mainLayout;
	QFormLayout *_formLayout;
	QGridLayout *_gridLayout;

	QMenuBar *_about;
	QMenu *_menu;
	QAction *_action;

	QVector<QLabel*> _currencyCollums;
	QVector<QLabel*> _valueCollums;

	QLabel *_valueLabel;
	QLabel *_currencyLabel;

	QLineEdit *_valueEdit;

	QComboBox *_currencyBox;
	
	QDate _dateToDay;
	QVector<Currency*> _currencyWired;
	RequestAPI *_parserRequest;
};

#endif

