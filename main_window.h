#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVector>
#include <QLayout>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QLocale>
#include <QDate>
#include <QStatusBar>
#include <QKeyEvent>
#include "currency.h"
#include "request_api.h"
#include "save_data.h"
#include "about.h"

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;
class QFormLayout;
class QMenuBar;
class QDateEdit;
class QMenu; 


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	void createAboutWindow();
	void convert();
	void onReplyAccept();
	void setEnableButton();
	void selectDate(const QDate &date);

	void displayResult();

	void createResultConvertBox();
	void createBaseCurrencyBox();

signals:
	void pressEnter();

private:
	QDateEdit *_calendar;

	QPushButton *_convertButton;

	QGroupBox *_gridGroupBox;
	QGroupBox *_formGroupBox;

	QVBoxLayout *_mainLayout;
	QFormLayout *_formLayout;
	QGridLayout *_gridLayout;

	QMenuBar *_about;
	QMenu *_menu;
	QAction *_action;

	QVector<QLabel*> _currencyColumns;
	QVector<QLabel*> _valueColumns;

	QLabel *_valueLabel;
	QLabel *_currencyLabel;

	QLineEdit *_valueEdit;

	QComboBox *_currencyBox;
	
	QDate _dateToDay;

	QMap<CurrenciesPair, double> _currencies;
	SaveData _saveData;

	RequestAPI *_parserRequest;
};

#endif

