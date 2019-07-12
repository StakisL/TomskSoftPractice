
#include <QDate>
#include "widget.h"
#include "about.h"


mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
	/*
	Èíèöèàëèçèðóþ âøèòûå â ïðèëîæåíèå âàëþòû.
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
    Ôóíêöèÿ ñîçäàåò GridLayout íà êîòîðîé îòîáðàæàþòñÿ
	Âàëþòû, èõ êóðñ è ïåðåâåäåííàÿ ñóììà.
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
    Ñîçäàåò FormLayout êîòîðûé ñëóæèò äëÿ ââîäà áàçîâîé âàëþòû è ñóììû
	äëÿ ïåðåâîäà, òàê æå ñîäåðæèò òåêóùóþ äàòó.
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
    Ñëîò îòïðàâëÿåò ãåò-çàïðîñ íà âíåøíóþ API
*/
void mainWindow::doConvert()
{
	parserRequest = new RequestAPI(currencyWired);
	connect(parserRequest, SIGNAL(replyAccepted()), this, SLOT(onReplyAccept()));
	parserRequest->getRequest();
	submitButton->setEnabled(false);
}

/*
    Ñëîò îáðàáàòûâàåò äàííûå ïîëó÷åííûå â ðåçóëüòàòå ãåò-çàïðîñà
*/
void mainWindow::onReplyAccept()
{
	QString takeBaseCurrency = currencyBox->currentText();
	currencyWired = parserRequest->getResultParse();
	int counterCollums = 0, temp = 0, baseCurrency = 0;
	
	for (int i = 0; i < currencyWired.size(); i++)
	{
		//Óñëîâèå óáèðàåò ïðåäûäóùåå áàçîâîå çíà÷åíèå.
		if (takeBaseCurrency != currencyWired[i]->getTypeCurrency() && currencyWired[i]->getBase())
		{
			currencyWired[i]->setBase(false);
		}

		/*
		Òàê êàê ãåò-çàïðîñ âîçâðàùàåò êóðñ âàëþò îòíîñèòåëüíî áàçîâîé,
		à åé ÿâëÿåòñÿ âñåãäà USD,äëÿ òîãî ÷òîáû âåðíî óñòíàíîâèòü çíà÷åíèÿ êîýôôèöèåíòîâ
		íàì íóæåí èíäåêñ îáúåêòà â êîòîðîì íàõîäèòñÿ âàëþòà USD
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

	//Óñòàíàâëèâàåì çíà÷åíèÿ áàçîâîé âàëþòû
	currencyWired[baseCurrency]->setBase(true);
	currencyWired[temp]->setRatioCurrency(double(1 / currencyWired[baseCurrency]->getRatioCurrency()));
	currencyWired[baseCurrency]->setRatioCurrency(1.0);

	
    //Ïåðåðàñ÷èòûâàåì êîýôôèöèåíòû äëÿ âàëþò îòíîñèòåëüíî áàçîâîé.
	for (int i = 0; i < currencyWired.size(); i++)
	{
		if (i != baseCurrency && i != temp)
		{
			currencyWired[i]->setRatioCurrency(double(currencyWired[temp]->getRatioCurrency()
				*currencyWired[i]->getRatioCurrency()));
		}
	}

	//Îòîáðàæàåì ðåçóëüòàòû â îñíîâíîì îêíå.
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
