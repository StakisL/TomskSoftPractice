
#include <QDate>
#include "widget.h"
#include "about.h"
#include "parse.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	/*
	Инициализирую вшитые в приложение валюты.
	*/
	currencyWired.push_back(new Currency("RUB"));
	currencyWired.push_back(new Currency("USD"));
	currencyWired.push_back(new Currency("EUR"));
	currencyWired.push_back(new Currency("AUD"));
	currencyWired.push_back(new Currency("JPY"));
	currencyWired.push_back(new Currency("CAD"));


	createFormGroupBox();
	createGridGroupBox();

	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(formGroupBox);
	mainLayout->addWidget(gridGroupBox);
	setLayout(mainLayout);
}


/*
    Функция создает GridLayout на которой отображаются
	Валюты, их курс и переведенная сумма.
*/
void Widget::createGridGroupBox()
{
	gridGroupBox = new QGroupBox(tr("Result convert"));
	gridLayout = new QGridLayout;
	
	for (int i = 0; i < NumGridRows; ++i)
	{
		currencyCollums[i] = new QLabel(tr("Currency %1:").arg(i + 1));
		gridLayout->addWidget(currencyCollums[i], i + 1, 1);
	}

	for (int i = 0; i < NumGridRows; ++i) 
	{
		valueCollums[i] = new QLabel(tr("Value :").arg(i + 1));
		gridLayout->addWidget(valueCollums[i], i + 1, 2);
	}

	gridLayout->setHorizontalSpacing(50);
	gridLayout->setColumnStretch(1, 10);
	gridLayout->setColumnStretch(2, 20);
	gridGroupBox->setLayout(gridLayout);
}


/*
    Создает FormLayout который служит для ввода базовой валюты и суммы
	для перевода, так же содержит текущую дату.
*/
void Widget::createFormGroupBox()
{
	QDate dateToDay = QDate::currentDate();
	formGroupBox = new QGroupBox(dateToDay.toString("dd.MM.yy"));
	formGroupBox->setFixedHeight(100);
	formLayout = new QFormLayout;


	aboutButton = new QPushButton("About");
	submitButton = new QPushButton("Submit");

	//aboutButton->setDefault(true);
	//submitButton->setDefault(true);

	valueLabel = new QLabel(tr("Value:"));
	currencyLabel = new QLabel(tr("Currency:"));

	valueEdit = new QLineEdit();
	currencyBox = new QComboBox();
	
	for (int i = 0; i < currencyWired.size(); i++)
	{
		currencyBox->addItem(currencyWired[i]->getTypeCurrency());
	}

	formLayout->addRow(valueLabel, valueEdit);
	formLayout->addRow(currencyLabel, currencyBox);
	formLayout->addRow(aboutButton,submitButton);
	formGroupBox->setLayout(formLayout);

	connect(aboutButton, SIGNAL(clicked()), this, SLOT(createWindow()));
	connect(submitButton, SIGNAL(clicked()), this, SLOT(doConvert()));
	
}


void Widget::doConvert()
{
	QString takeBaseCurrency = currencyBox->currentText();
	int j = 0;
	for (int i = 0; i < currencyWired.size(); i++)
	{
		if (takeBaseCurrency == currencyWired[i]->getTypeCurrency())
		{
			currencyWired[i]->setBase(true);
			currencyWired[i]->setRatioCurrency(1.0);
		}
		else
		{
			currencyCollums[j]->setText(currencyWired[i]->getTypeCurrency() + ":");
			j++;
		}
	}

	RequestAPI *parserRequest = new RequestAPI(currencyWired);
	parserRequest->getRequest();
	currencyWired = parserRequest->getResultParse();


	/*for (int i = 0; i < NumGridRows; ++i)
	{
		
		valueCollums[i]->setText(QString::number(currencyWired[i]->getRatioCurrency()));
	}
*/
}


void Widget::createWindow()
{
	About about;
	about.exec();
}


Widget::~Widget()
{
}
