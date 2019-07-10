
#include <QDate>
#include "widget.h"
#include "about.h"


mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
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
void mainWindow::createGridGroupBox()
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
void mainWindow::createFormGroupBox()
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

/*
    Слот отправляет гет-запрос на внешную API
*/
void mainWindow::doConvert()
{
	parserRequest = new RequestAPI(currencyWired);
	connect(parserRequest, SIGNAL(replyAccepted()), this, SLOT(onReplyAccept()));
	parserRequest->getRequest();
	submitButton->setEnabled(false);
}

/*
    Слот обрабатывает данные полученные в результате гет-запроса
*/
void mainWindow::onReplyAccept()
{
	QString takeBaseCurrency = currencyBox->currentText();
	currencyWired = parserRequest->getResultParse();
	int counterCollums = 0, temp = 0, baseCurrency = 0;
	
	for (int i = 0; i < currencyWired.size(); i++)
	{
		//Условие убирает предыдущее базовое значение.
		if (takeBaseCurrency != currencyWired[i]->getTypeCurrency() && currencyWired[i]->getBase())
		{
			currencyWired[i]->setBase(false);
		}

		/*
		Так как гет-запрос возвращает курс валют относительно базовой,
		а ей является всегда USD,для того чтобы верно устнановить значения коэффициентов
		нам нужен индекс объекта в котором находится валюта USD
		*/
		if (currencyWired[i]->getTypeCurrency() == "USD")
		{
			temp = i;
		}

		if (takeBaseCurrency == currencyWired[i]->getTypeCurrency())
		{
			baseCurrency = i;
		}
	}

	//Устанавливаем значения базовой валюты
	currencyWired[baseCurrency]->setBase(true);
	currencyWired[temp]->setRatioCurrency(double(1 / currencyWired[baseCurrency]->getRatioCurrency()));
	currencyWired[baseCurrency]->setRatioCurrency(1.0);

	
    //Перерасчитываем коэффициенты для валют относительно базовой.
	for (int i = 0; i < currencyWired.size(); i++)
	{
		if (i != baseCurrency && i != temp)
		{
			currencyWired[i]->setRatioCurrency(double(currencyWired[temp]->getRatioCurrency()
				*currencyWired[i]->getRatioCurrency()));
		}
	}

	//Отображаем результаты в основном окне.
	for (int i = 0; i < currencyWired.size(); ++i)
	{
		if (!currencyWired[i]->getBase())
		{
			currencyCollums[counterCollums]->setText(currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(currencyWired[i]->getRatioCurrency()));

			valueCollums[counterCollums]->setText(currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(currencyWired[i]->getValue((valueEdit->text().toInt()))));
			counterCollums++;
		}

	}
	submitButton->setEnabled(true);
}



void mainWindow::createWindow()
{
	About about;
	about.exec();
}


mainWindow::~mainWindow()
{
	if (parserRequest != nullptr)
	{
		delete parserRequest;
	}
}
