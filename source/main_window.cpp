#include "main_window.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	createCurrencyMap(_currencies);
	_parserRequest = new RequestManager();

	createBaseCurrencyBox();
	createResultConvertBox();

	_waitedTime = new QTimer(this);

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
	
	
	connect(_parserRequest, &RequestManager::replyAccepted, this, &MainWindow::onReplyAccept);
	connect(_parserRequest, &RequestManager::replyError, this, &MainWindow::requestError);
	connect(_action, &QAction::triggered, this, []()
	{
		About about;
		about.exec();
	});
}


void MainWindow::createResultConvertBox()
{
	_gridGroupBox = new QGroupBox(this);
	_gridLayout = new QGridLayout(this);

	const int  countColumns = 6;

	_valueColumns.push_back(new QLabel(tr("Value:")));
	_currencyColumns.push_back(new QLabel(tr("Currencies:")));

	_gridLayout->addWidget(_valueColumns[0], 0, 2);
	_gridLayout->addWidget(_currencyColumns[0], 0, 1);

	for (int i = 1; i < countColumns; ++i)
	{
		_currencyColumns.push_back(new QLabel(tr("Currency %1:").arg(i + 1)));
		_gridLayout->addWidget(_currencyColumns[i], i + 1, 1);
	}

	for (int i = 1; i < countColumns; ++i)
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
	_formGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	_formLayout = new QFormLayout(this);

	_valueEdit = new QLineEdit();
	/*Устанавливаю правила ввода в lineEdit(только числа, максимум 6,
	с максимум 3 знаками после запятой*/
	_valueEdit->setValidator(new QRegExpValidator
	(QRegExp("[0-9]{0,6}[.]{0,1}[0-9]{0,3}$")));

	_currencyBox = new ComboBox();
	_currencyBox->addItem("USD");
	_currencyBox->addItem("AUD");
	_currencyBox->addItem("CAD");
	_currencyBox->addItem("RUB");
	_currencyBox->addItem("JPY");
	_currencyBox->addItem("EUR");

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
	connect(this, &MainWindow::pressedEnter, &MainWindow::convert);
	connect(_convertButton, &QPushButton::clicked, this, &MainWindow::convert);
	connect(_calendar, &QDateEdit::dateChanged, this, &MainWindow::selectDate);
}

void MainWindow::setEnableButton()
{
	_convertButton->setEnabled(!_valueEdit->text().isEmpty());
}

void MainWindow::convert()
{
	_convertButton->setEnabled(false);
	if (_saveData.checkData(_dateToDay))
	{
		_saveData.loadValue(_currencies, _dateToDay);
		displayResult();
		_convertButton->setEnabled(true);
	}
	else
	{
		connect(_waitedTime, &QTimer::timeout, this, &MainWindow::timeoutError);
		_waitedTime->start(3000);
		_parserRequest->getRequest(_dateToDay);
	}
}

void MainWindow::onReplyAccept()
{
	_waitedTime->stop();
	disconnect(_waitedTime, &QTimer::timeout, this, &MainWindow::timeoutError);
	_parserRequest->getResultParse(_currencies);
	displayResult();

	_saveData.saveValue(_currencies, _dateToDay);

	_convertButton->setEnabled(true);
}

void MainWindow::timeoutError()
{
	disconnect(_waitedTime, &QTimer::timeout, this, &MainWindow::timeoutError);
	_convertButton->setEnabled(true);
	_errorBox.setText("Error,check internet connection");
	_errorBox.exec();
}

void MainWindow::requestError(const QString &error)
{
	if (error.contains("302"))
	{
		_errorBox.setText("Maximum number of conversions per hour exceeded!");
		_errorBox.exec();
	}
	else if (error.contains("3"))
	{
		_errorBox.setText("Error, server is not response!");
		_errorBox.exec();
	}
	_convertButton->setEnabled(true);
}

void MainWindow::displayResult()
{
	int _countColumns = 1;
	////Отображаем результаты в основном окне.
	for (int i = 0; i < _currencies.size(); ++i)
	{
		auto currency = _currencies.keys().at(i);
		if (_currencyBox->currentItem() == currency.first)
		{
			_currencyColumns[_countColumns]->setText(currencyTypeToString(currency.second) + ": "
				+ QString::number(_currencies[CurrenciesPair(currency.first,
					currency.second)], 'f', 4));

			_valueColumns[_countColumns]->setText(QString::number(_currencies
				[CurrenciesPair(currency.first, currency.second)]
					*((_valueEdit->text().toDouble())),'f', 4));
			_countColumns++;
		}
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		emit pressedEnter();
	}

	QWidget::keyPressEvent(event);
}

void MainWindow::selectDate(const QDate &date)
{
	_dateToDay = date;
}

MainWindow::~MainWindow() = default;
