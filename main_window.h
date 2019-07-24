#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVector>
#include <QLayout>
#include <QMenu>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QMenuBar>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QLocale>
#include <QDate>
#include <QStatusBar>
#include <QKeyEvent>
#include <QMessageBox>
#include "about.h"
#include "currency.h"
#include "request_manager.h"
#include "save_data.h"


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
	void convert();
	void onReplyAccept();
	void setEnableButton();
	void selectDate(const QDate &date);
	void requestError(const QString &error);

	void displayResult();

	void createResultConvertBox();
	void createBaseCurrencyBox();

signals:
	void pressedEnter();

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
	QMessageBox _errorBox;

	QDate _dateToDay;

	QMap<CurrenciesPair, double> _currencies;
	SaveData _saveData;
	RequestManager *_parserRequest;
};

#endif

