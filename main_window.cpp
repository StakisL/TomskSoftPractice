<<<<<<< HEAD
#include <QDate>
#include "main_window.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	_currencyWired.push_back(new Currency("RUB"));
	_currencyWired.push_back(new Currency("USD"));
	_currencyWired.push_back(new Currency("EUR"));
	_currencyWired.push_back(new Currency("AUD"));
	_currencyWired.push_back(new Currency("JPY"));
	_currencyWired.push_back(new Currency("CAD"));
	_parserRequest = new RequestAPI(_currencyWired);

	createBaseCurrencyBox();
	createResultConvertBox();

	_about = new QMenuBar(this);
	QMenu *menu = new QMenu("&Help");
	QAction *action = menu->addAction("&About");
	connect(action, &QAction::triggered, this, &MainWindow::createAboutWindow);
	_about->addMenu(menu);
	_about->show();

	_mainLayout = new QVBoxLayout(this);
	_mainLayout->addWidget(_about);
	_mainLayout->addWidget(_formGroupBox);
	_mainLayout->addWidget(_gridGroupBox);
	
	setLayout(_mainLayout);
}


/*
    ������� ������� GridLayout �� ������� ������������
	������, �� ���� � ������������ �����.
*/
void MainWindow::createResultConvertBox()
{
	_gridGroupBox = new QGroupBox(tr("Result convert"),this);
	_gridLayout = new QGridLayout(this);
	const int  countCollums = 5;

	for (int i = 0; i < countCollums; ++i)
	{
		_currencyCollums.push_back(new QLabel(tr("Currency %1:").arg(i + 1)));
		_gridLayout->addWidget(_currencyCollums[i], i + 1, 1);
	}

	for (int i = 0; i < countCollums; ++i)
	{
		_valueCollums.push_back(new QLabel(tr("Value :").arg(i + 1)));
		_gridLayout->addWidget(_valueCollums[i], i + 1, 2);
	}

	_gridLayout->setHorizontalSpacing(50);
	_gridLayout->setColumnStretch(1, 10);
	_gridLayout->setColumnStretch(2, 20);
	_gridGroupBox->setLayout(_gridLayout);
}


/*
    ������� FormLayout ������� ������ ��� ����� ������� ������ � �����
	��� ��������, ��� �� �������� ������� ����.
*/
void MainWindow::createBaseCurrencyBox()
{
	QDate dateToDay = QDate::currentDate();
	_formGroupBox = new QGroupBox(dateToDay.toString("dd.MM.yy"),this);
	_formGroupBox->setFixedHeight(100);
	_formLayout = new QFormLayout(this);

	_submitButton = new QPushButton("Submit",this);
	_submitButton->setDisabled(true);

	_valueLabel = new QLabel(tr("Value:"),this);
	_currencyLabel = new QLabel(tr("Currency:"),this);

	_valueEdit = new QLineEdit();
	/*������������ ������� ����� � lineEdit(������ �����, �������� 6,
	� �������� 3 ������� ����� �������*/
	_valueEdit->setValidator(new QRegExpValidator
	(QRegExp("[0-9]{0,6}\[.]{0,1}\[0-9]{0,3}$")));
	connect(_valueEdit, &QLineEdit::textEdited, this, &MainWindow::setEnableButton);
	_currencyBox = new QComboBox(this);
	
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		_currencyBox->addItem(_currencyWired[i]->getTypeCurrency());
	}

	_formLayout->addRow(_valueLabel, _valueEdit);
	_formLayout->addRow(_currencyLabel, _currencyBox);
	_formLayout->addRow(_submitButton);
	_formGroupBox->setLayout(_formLayout);

	connect(_submitButton, &QPushButton::clicked, this, &MainWindow::doConvert);
	
}

void MainWindow::setEnableButton()
{
	if (!_valueEdit->text().isEmpty())
	{
		_submitButton->setEnabled(true);
	}
	if (_valueEdit->text().isEmpty())
	{
		_submitButton->setEnabled(false);
	}
}
/*
    ���� ���������� ���-������ �� ������� API
*/
void MainWindow::doConvert()
{
	connect(_parserRequest, &RequestAPI::replyAccepted, this, &MainWindow::onReplyAccept);
	_parserRequest->getRequest();
	_submitButton->setEnabled(false);
}

/*
    ���� ������������ ������ ���������� � ���������� ���-�������
*/
void MainWindow::onReplyAccept()
{
	QString takeBaseCurrency = _currencyBox->currentText();
	_currencyWired = _parserRequest->getResultParse();
	int counterCollums = 0, temp = 0, baseCurrency = 0;
	
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		//������� ������� ���������� ������� ��������.
		if (takeBaseCurrency != _currencyWired[i]->getTypeCurrency() && _currencyWired[i]->getBase())
		{
			_currencyWired[i]->setBase(false);
		}

		/*
		��� ��� ���-������ ���������� ���� ����� ������������ �������,
		� �� �������� ������ USD,��� ���� ����� ����� ����������� �������� �������������
		��� ����� ������ ������� � ������� ��������� ������ USD
		*/
		if (_currencyWired[i]->getTypeCurrency() == "USD")
		{
			temp = i;
		}

		if (takeBaseCurrency == _currencyWired[i]->getTypeCurrency())
		{
			baseCurrency = i;
		}
	}

	//������������� �������� ������� ������
	_currencyWired[baseCurrency]->setBase(true);
	_currencyWired[temp]->setRatioCurrency(double(1 / _currencyWired[baseCurrency]->getRatioCurrency()));
	_currencyWired[baseCurrency]->setRatioCurrency(1.0);

	
    //��������������� ������������ ��� ����� ������������ �������.
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		if (i != baseCurrency && i != temp)
		{
			_currencyWired[i]->setRatioCurrency(double(_currencyWired[temp]->getRatioCurrency()
				*_currencyWired[i]->getRatioCurrency()));
		}
	}

	//���������� ���������� � �������� ����.
	for (int i = 0; i < _currencyWired.size(); ++i)
	{
		if (!_currencyWired[i]->getBase())
		{
			_currencyCollums[counterCollums]->setText(_currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(_currencyWired[i]->getRatioCurrency()));

			_valueCollums[counterCollums]->setText(_currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(_currencyWired[i]->getValue((_valueEdit->text().toDouble()))));
			counterCollums++;
		}

	}
	_submitButton->setEnabled(true);
}



void MainWindow::createAboutWindow()
{
	About about;
	about.exec();
}


MainWindow::~MainWindow()
{
	
}
=======

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
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
