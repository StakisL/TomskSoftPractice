#include "request_api.h"

RequestAPI::RequestAPI(QMap<CurrenciesPair, double> currencies, QNetworkAccessManager *parent)
	: QNetworkAccessManager(parent)
{
	_currencies = currencies;
	_error = false;
}

void RequestAPI::getRequest(QDate date)
{
	int i = 0; 
	_date = date;

	/*
	Используемая API разрешает сделать запрос только 10 преобразований за 1 раз,
	для получение полного списка валют за день, используем в качестве общего запроса,
	сразу 3 запроса.
	*/
	_urlFirst.setUrl(QString("http://free.currconv.com/api/v7/convert?q="
		"USD_AUD,USD_CAD,USD_EUR,USD_JPY,USD_RUB,"
		"RUB_AUD,RUB_CAD,RUB_EUR,RUB_JPY,RUB_USD"
		"&compact=ultra&date=%1&apiKey=9942582d9e7fb170c046")
		.arg(date.toString("yyyy-MM-dd")));

	_urlSecond.setUrl(QString("http://free.currconv.com/api/v7/convert?q="
		"AUD_CAD,AUD_EUR,AUD_JPY,AUD_USD,AUD_RUB,"
		"CAD_AUD,CAD_EUR,CAD_JPY,CAD_USD,CAD_RUB"
		"&compact=ultra&date=%1&apiKey=9942582d9e7fb170c046")
		.arg(date.toString("yyyy-MM-dd")));

	_urlThird.setUrl(QString("http://free.currconv.com/api/v7/convert?q="
		"EUR_AUD,EUR_JPY,EUR_CAD,EUR_USD,EUR_RUB,"
		"JPY_AUD,JPY_EUR,JPY_CAD,JPY_USD,JPY_RUB"
		"&compact=ultra&date=%1&apiKey=9942582d9e7fb170c046")
		.arg(date.toString("yyyy-MM-dd")));

	_countRequestSignals = 0;
	makeRequest(_urlFirst);
	makeRequest(_urlSecond);
	makeRequest(_urlThird);
}

void RequestAPI::makeRequest(QUrl url)
{
	_manager = new QNetworkAccessManager();
	_reply = _manager->get(QNetworkRequest(url));
	connect(_reply, &QNetworkReply::finished, this, &RequestAPI::replyFinished);
}

void RequestAPI::replyFinished()
{
	_reply = qobject_cast<QNetworkReply *>(sender());

	if (_reply->error() == QNetworkReply::NoError)
	{
		QJsonDocument content = QJsonDocument::fromJson(_reply->readAll());
		_resultRequest.enqueue(content.object());
		_reply->deleteLater();

		_countRequestSignals++;

		if (_countRequestSignals == 3 && !_error)
		{
			_countRequestSignals = 0;
			emit replyAccepted();
		}
	}
	else
	{
		_countRequestSignals++;
		_error = true;
		_textError = _reply->error();

		if (_countRequestSignals == 3 && _error)
		{
			_countRequestSignals = 0;
			_error = false;
			emit replyError(_textError);
		}
	}
}


QMap<CurrenciesPair, double> RequestAPI::getResultParse()
{
	while(!_resultRequest.empty())
	{
		QJsonObject root = _resultRequest.dequeue();
		QJsonObject innerRoot;

		for (int i = 0; i < _currencies.size(); i++)
		{
			for (int j = 0; j < root.size(); j++)
			{
				if (root.keys().at(j).contains(QString(currencyTypeToString(_currencies.keys().at(i).first)
					+ "_" + (currencyTypeToString(_currencies.keys().at(i).second)))))
				{
					innerRoot = root[root.keys().at(j)].toObject();
					_currencies[CurrenciesPair(_currencies.keys().at(i).first, _currencies.keys().at(i).second)] =
						innerRoot[_date.toString("yyyy-MM-dd")].toDouble();
				}
			}
		}
	}
	return _currencies;
}

RequestAPI::~RequestAPI() 
{
	if (_reply != nullptr)
		_reply->deleteLater();
}
