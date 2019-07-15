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

	_parserRequest = new RequestAPI();
	connect(_parserRequest, &RequestAPI::replyAccepted, this, &MainWindow::onReplyAccept);

	createBaseCurrencyBox();
	createResultConvertBox();

	_about = new QMenuBar(this);
	_about->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
	int baseCurrencyIndex = 0;

	for (int i = 0; i < _currencyWired.size(); i++)
	{
		if (_currencyWired[i]->getTypeCurrency() == _currencyBox->currentText())
		{
			baseCurrencyIndex = i;
		}
	}
	_currencyWired.move(baseCurrencyIndex, 0);

	_parserRequest->getRequest(_currencyWired);
	_submitButton->setEnabled(false);
}

/*
    Слот обрабатывает данные полученные в результате гет-запроса
*/
void MainWindow::onReplyAccept()
{
	_currencyWired = _parserRequest->getResultParse();
	int counterCollums = 0;
	//Отображаем результаты в основном окне.
	for (int i = 1; i < _currencyWired.size(); ++i)
	{
			_currencyCollums[counterCollums]->setText(_currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(_currencyWired[i]->getRatioCurrency()));

			_valueCollums[counterCollums]->setText(_currencyWired[i]->getTypeCurrency() + ": "
				+ QString::number(_currencyWired[i]->getValue((_valueEdit->text().toDouble()))));
			counterCollums++;
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
