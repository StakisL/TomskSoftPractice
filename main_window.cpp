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
    Функция создает GridLayout на которой отображаются
	Валюты, их курс и переведенная сумма.
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
    Создает FormLayout который служит для ввода базовой валюты и суммы
	для перевода, так же содержит текущую дату.
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
	/*Устанавливаю правила ввода в lineEdit(только числа, максимум 6,
	с максимум 3 знаками после запятой*/
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
    Слот отправляет гет-запрос на внешную API
*/
void MainWindow::doConvert()
{
	connect(_parserRequest, &RequestAPI::replyAccepted, this, &MainWindow::onReplyAccept);
	_parserRequest->getRequest();
	_submitButton->setEnabled(false);
}

/*
    Слот обрабатывает данные полученные в результате гет-запроса
*/
void MainWindow::onReplyAccept()
{
	QString takeBaseCurrency = _currencyBox->currentText();
	_currencyWired = _parserRequest->getResultParse();
	int counterCollums = 0, temp = 0, baseCurrency = 0;
	
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		//Условие убирает предыдущее базовое значение.
		if (takeBaseCurrency != _currencyWired[i]->getTypeCurrency() && _currencyWired[i]->getBase())
		{
			_currencyWired[i]->setBase(false);
		}

		/*
		Так как гет-запрос возвращает курс валют относительно базовой,
		а ей является всегда USD,для того чтобы верно устнановить значения коэффициентов
		нам нужен индекс объекта в котором находится валюта USD
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

	//Устанавливаем значения базовой валюты
	_currencyWired[baseCurrency]->setBase(true);
	_currencyWired[temp]->setRatioCurrency(double(1 / _currencyWired[baseCurrency]->getRatioCurrency()));
	_currencyWired[baseCurrency]->setRatioCurrency(1.0);

	
    //Перерасчитываем коэффициенты для валют относительно базовой.
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		if (i != baseCurrency && i != temp)
		{
			_currencyWired[i]->setRatioCurrency(double(_currencyWired[temp]->getRatioCurrency()
				*_currencyWired[i]->getRatioCurrency()));
		}
	}

	//Отображаем результаты в основном окне.
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
	Г€Г­ГЁГ¶ГЁГ Г«ГЁГ§ГЁГ°ГіГѕ ГўГёГЁГІГ»ГҐ Гў ГЇГ°ГЁГ«Г®Г¦ГҐГ­ГЁГҐ ГўГ Г«ГѕГІГ».
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
    Г”ГіГ­ГЄГ¶ГЁГї Г±Г®Г§Г¤Г ГҐГІ GridLayout Г­Г  ГЄГ®ГІГ®Г°Г®Г© Г®ГІГ®ГЎГ°Г Г¦Г ГѕГІГ±Гї
	Г‚Г Г«ГѕГІГ», ГЁГµ ГЄГіГ°Г± ГЁ ГЇГҐГ°ГҐГўГҐГ¤ГҐГ­Г­Г Гї Г±ГіГ¬Г¬Г .
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
    Г‘Г®Г§Г¤Г ГҐГІ FormLayout ГЄГ®ГІГ®Г°Г»Г© Г±Г«ГіГ¦ГЁГІ Г¤Г«Гї ГўГўГ®Г¤Г  ГЎГ Г§Г®ГўГ®Г© ГўГ Г«ГѕГІГ» ГЁ Г±ГіГ¬Г¬Г»
	Г¤Г«Гї ГЇГҐГ°ГҐГўГ®Г¤Г , ГІГ ГЄ Г¦ГҐ Г±Г®Г¤ГҐГ°Г¦ГЁГІ ГІГҐГЄГіГ№ГіГѕ Г¤Г ГІГі.
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
    Г‘Г«Г®ГІ Г®ГІГЇГ°Г ГўГ«ГїГҐГІ ГЈГҐГІ-Г§Г ГЇГ°Г®Г± Г­Г  ГўГ­ГҐГёГ­ГіГѕ API
*/
void mainWindow::doConvert()
{
	parserRequest = new RequestAPI(currencyWired);
	connect(parserRequest, SIGNAL(replyAccepted()), this, SLOT(onReplyAccept()));
	parserRequest->getRequest();
	submitButton->setEnabled(false);
}

/*
    Г‘Г«Г®ГІ Г®ГЎГ°Г ГЎГ ГІГ»ГўГ ГҐГІ Г¤Г Г­Г­Г»ГҐ ГЇГ®Г«ГіГ·ГҐГ­Г­Г»ГҐ Гў Г°ГҐГ§ГіГ«ГјГІГ ГІГҐ ГЈГҐГІ-Г§Г ГЇГ°Г®Г±Г 
*/
void mainWindow::onReplyAccept()
{
	QString takeBaseCurrency = currencyBox->currentText();
	currencyWired = parserRequest->getResultParse();
	int counterCollums = 0, temp = 0, baseCurrency = 0;
	
	for (int i = 0; i < currencyWired.size(); i++)
	{
		//Г“Г±Г«Г®ГўГЁГҐ ГіГЎГЁГ°Г ГҐГІ ГЇГ°ГҐГ¤Г»Г¤ГіГ№ГҐГҐ ГЎГ Г§Г®ГўГ®ГҐ Г§Г­Г Г·ГҐГ­ГЁГҐ.
		if (takeBaseCurrency != currencyWired[i]->getTypeCurrency() && currencyWired[i]->getBase())
		{
			currencyWired[i]->setBase(false);
		}

		/*
		Г’Г ГЄ ГЄГ ГЄ ГЈГҐГІ-Г§Г ГЇГ°Г®Г± ГўГ®Г§ГўГ°Г Г№Г ГҐГІ ГЄГіГ°Г± ГўГ Г«ГѕГІ Г®ГІГ­Г®Г±ГЁГІГҐГ«ГјГ­Г® ГЎГ Г§Г®ГўГ®Г©,
		Г  ГҐГ© ГїГўГ«ГїГҐГІГ±Гї ГўГ±ГҐГЈГ¤Г  USD,Г¤Г«Гї ГІГ®ГЈГ® Г·ГІГ®ГЎГ» ГўГҐГ°Г­Г® ГіГ±ГІГ­Г Г­Г®ГўГЁГІГј Г§Г­Г Г·ГҐГ­ГЁГї ГЄГ®ГЅГґГґГЁГ¶ГЁГҐГ­ГІГ®Гў
		Г­Г Г¬ Г­ГіГ¦ГҐГ­ ГЁГ­Г¤ГҐГЄГ± Г®ГЎГєГҐГЄГІГ  Гў ГЄГ®ГІГ®Г°Г®Г¬ Г­Г ГµГ®Г¤ГЁГІГ±Гї ГўГ Г«ГѕГІГ  USD
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

	//Г“Г±ГІГ Г­Г ГўГ«ГЁГўГ ГҐГ¬ Г§Г­Г Г·ГҐГ­ГЁГї ГЎГ Г§Г®ГўГ®Г© ГўГ Г«ГѕГІГ»
	currencyWired[baseCurrency]->setBase(true);
	currencyWired[temp]->setRatioCurrency(double(1 / currencyWired[baseCurrency]->getRatioCurrency()));
	currencyWired[baseCurrency]->setRatioCurrency(1.0);

	
    //ГЏГҐГ°ГҐГ°Г Г±Г·ГЁГІГ»ГўГ ГҐГ¬ ГЄГ®ГЅГґГґГЁГ¶ГЁГҐГ­ГІГ» Г¤Г«Гї ГўГ Г«ГѕГІ Г®ГІГ­Г®Г±ГЁГІГҐГ«ГјГ­Г® ГЎГ Г§Г®ГўГ®Г©.
	for (int i = 0; i < currencyWired.size(); i++)
	{
		if (i != baseCurrency && i != temp)
		{
			currencyWired[i]->setRatioCurrency(double(currencyWired[temp]->getRatioCurrency()
				*currencyWired[i]->getRatioCurrency()));
		}
	}

	//ГЋГІГ®ГЎГ°Г Г¦Г ГҐГ¬ Г°ГҐГ§ГіГ«ГјГІГ ГІГ» Гў Г®Г±Г­Г®ГўГ­Г®Г¬ Г®ГЄГ­ГҐ.
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
