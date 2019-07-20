#include "main_window.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	_currencyWired.push_back(new Currency("RUB"));
	_currencyWired.push_back(new Currency("USD"));
	_currencyWired.push_back(new Currency("EUR"));
	_currencyWired.push_back(new Currency("AUD"));
	_currencyWired.push_back(new Currency("JPY"));
	_currencyWired.push_back(new Currency("CAD"));

	_parserRequest = new RequestAPI();

	createBaseCurrencyBox();
	createResultConvertBox();

	_about = new QMenuBar(this);
	_about->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	_menu = new QMenu("&Help");
	_action = _menu->addAction("&About");
	
	_about->addMenu(_menu);
	_about->show();

	_mainLayout = new QVBoxLayout(this);
	_mainLayout->setMenuBar(_about);
	_mainLayout->addWidget(_formGroupBox);
	_mainLayout->addWidget(_gridGroupBox);
	setLayout(_mainLayout);
	
	connect(_parserRequest, &RequestAPI::replyAccepted, this, &MainWindow::onReplyAccept);
	connect(_action, &QAction::triggered, this, &MainWindow::createAboutWindow);
}


void MainWindow::createResultConvertBox()
{
	_gridGroupBox = new QGroupBox(tr("Result convert"),this);
	_gridLayout = new QGridLayout(this);
	const int  countCollums = 6;

	_valueColumns.push_back(new QLabel(tr("Value:")));
	_currencyColumns.push_back(new QLabel(tr("Currencies:")));
	_gridLayout->addWidget(_valueColumns[0], 0, 2);
	_gridLayout->addWidget(_currencyColumns[0], 0, 1);

	for (int i = 1; i < countCollums; ++i)
	{
		_currencyColumns.push_back(new QLabel(tr("Currency %1:").arg(i + 1)));
		_gridLayout->addWidget(_currencyColumns[i], i + 1, 1);
	}

	for (int i = 1; i < countCollums; ++i)
	{
		_valueColumns.push_back(new QLabel(tr("Value :").arg(i + 1)));
		_gridLayout->addWidget(_valueColumns[i], i + 1, 2);
	}

	_gridLayout->setHorizontalSpacing(50);
	_gridLayout->setColumnStretch(1, 10);
	_gridLayout->setColumnStretch(2, 20);
	_gridGroupBox->setLayout(_gridLayout);
}


void MainWindow::createBaseCurrencyBox()
{
	_formGroupBox = new QGroupBox(this);
	_formGroupBox->setFixedHeight(100);
	_formLayout = new QFormLayout(this);

	_valueEdit = new QLineEdit();
	/*Устанавливаю правила ввода в lineEdit(только числа, максимум 6,
	с максимум 3 знаками после запятой*/
	_valueEdit->setValidator(new QRegExpValidator
	(QRegExp("[0-9]{0,6}[.]{0,1}[0-9]{0,3}$")));

	_currencyBox = new QComboBox(this);
	for (int i = 0; i < _currencyWired.size(); i++)
	{
		_currencyBox->addItem(_currencyWired[i]->getTypeCurrency());
	}

	_dateToDay = _dateToDay.currentDate();
	QDate minimumDate(_dateToDay.year() - 1, _dateToDay.month(),
		_dateToDay.day());

	_calendar = new QDateEdit(this);
	_calendar->setDateRange(minimumDate, _dateToDay);
	_calendar->setCalendarPopup(true);
	_calendar->setDate(_dateToDay);

	_convertButton = new QPushButton("Convert",this);
	_convertButton->setDisabled(true);

	_valueLabel = new QLabel(tr("Value:"),this);
	_currencyLabel = new QLabel(tr("Currency:"),this);

	_formLayout->addRow(_valueLabel, _valueEdit);
	_formLayout->addRow(_currencyLabel, _currencyBox);
	_formLayout->addRow(_calendar, _convertButton);
	_formGroupBox->setLayout(_formLayout);

	_valueEdit->setFocus();

	connect(_valueEdit, &QLineEdit::textEdited, this, &MainWindow::setEnableButton);
	connect(this, &MainWindow::pressEnter, &MainWindow::convert);
	connect(_convertButton, &QPushButton::clicked, this, &MainWindow::convert);
	connect(_calendar, &QDateEdit::dateChanged, this, &MainWindow::selectDate);
}


void MainWindow::setEnableButton()
{
	_convertButton->setEnabled(!_valueEdit->text().isEmpty());
}


void MainWindow::convert()
{
	int baseCurrencyIndex = 0;

	if (_convertButton->isEnabled())
	{
		for (int i = 0; i < _currencyWired.size(); i++)
		{
			if (_currencyWired[i]->getTypeCurrency() == _currencyBox->currentText())
			{
				baseCurrencyIndex = i;
			}
		}
		_currencyWired.move(baseCurrencyIndex, 0);

		//Проверяем существует ли актуальные данные в файле
		if (_saveData.checkData(_currencyWired[0]->getTypeCurrency(),
			_dateToDay))
		{
			//Записываем актуальые данные
			_currencyWired = _saveData.loadValue(_currencyWired[0]->getTypeCurrency(),
				_dateToDay);

			displayResult();
		}
		else
		{
			_parserRequest->getRequest(_currencyWired, _dateToDay);
			_convertButton->setEnabled(false);
		}
	}
}


void MainWindow::onReplyAccept()
{
	_currencyWired = _parserRequest->getResultParse();
	displayResult();
	_saveData.saveData(_currencyWired, _dateToDay);
	_convertButton->setEnabled(true);
}

void MainWindow::displayResult()
{
	
	//Отображаем результаты в основном окне.
	for (int i = 1; i < _currencyWired.size(); ++i)
	{
		_currencyColumns[i]->setText(_currencyWired[i]->getTypeCurrency() + ": "
			+ QString::number(_currencyWired[i]->getRatioCurrency()));

		_valueColumns[i]->setText(QString::number(_currencyWired[i]->getValue
		((_valueEdit->text().toDouble()))));

	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		emit pressEnter();
	}
}

void MainWindow::selectDate(const QDate &date)
{
	_dateToDay = date;
}


void MainWindow::createAboutWindow()
{
	About about;
	about.exec();
}


MainWindow::~MainWindow() {}
