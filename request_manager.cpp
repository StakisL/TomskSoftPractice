#include "request_manager.h"

RequestManager::RequestManager(QObject *parent)
	: QNetworkAccessManager(parent)
{
	_error = false;
}

void RequestManager::getRequest(const QDate &date)
{
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

void RequestManager::makeRequest(const QUrl &url)
{
	_reply = get(QNetworkRequest(url));
	connect(_reply, &QNetworkReply::finished, this, &RequestManager::replyFinished);
}

void RequestManager::replyFinished()
{
	_reply = qobject_cast<QNetworkReply *>(sender());

	if (_reply->error() == QNetworkReply::NoError)
	{
		QJsonDocument content = QJsonDocument::fromJson(_reply->readAll());
		_resultRequest.enqueue(content.object());
		_reply->deleteLater();
		_countRequestSignals++;
	}
	else
	{
		_countRequestSignals++;
		_error = true;
		_textError = _reply->error();
	}

	if (_countRequestSignals == 3 && _error)
	{
		_countRequestSignals = 0;
		_error = false;
		emit replyError(_textError);
	}
	else if (_countRequestSignals == 3 && !_error)
	{
		_countRequestSignals = 0;
		emit replyAccepted();
	}
}


void RequestManager::getResultParse(QMap<CurrenciesPair, double> &currencies)
{
	while(!_resultRequest.empty())
	{
		QJsonObject root = _resultRequest.dequeue();
		QJsonObject innerRoot;

		for (int i = 0; i < currencies.size(); i++)
		{
			for (int j = 0; j < root.size(); j++)
			{
				auto currency = currencies.keys().at(i);
				if (root.keys().at(j).contains(QString(currencyTypeToString(currency.first)
					+ "_" + (currencyTypeToString(currency.second)))))
				{
					innerRoot = root[root.keys().at(j)].toObject();
					currencies[CurrenciesPair(currency.first, currency.second)] =
						innerRoot[_date.toString("yyyy-MM-dd")].toDouble();
				}
			}
		}
	}
}

RequestManager::~RequestManager() 
{
	if (_reply != nullptr)
		_reply->deleteLater();
}
