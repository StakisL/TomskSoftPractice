#include "request_api.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

RequestAPI::RequestAPI(QNetworkAccessManager *parent) 
	: QNetworkAccessManager(parent)
{
	_manager = new QNetworkAccessManager();
}

void RequestAPI::getRequest(QVector<Currency*> currency)
{
	int i = 0;
	_currencyWired = currency;
	_url.setUrl(QString("http://free.currconv.com/api/v7/convert?q="
		"%1_%2,%1_%3,%1_%4,%1_%5,%1_%6&compact=ultra&apiKey=9942582d9e7fb170c046")
		.arg(_currencyWired[0]->getTypeCurrency()).arg(_currencyWired[1]->getTypeCurrency())
		.arg(_currencyWired[2]->getTypeCurrency()).arg(_currencyWired[3]->getTypeCurrency())
		.arg(_currencyWired[4]->getTypeCurrency()).arg(_currencyWired[5]->getTypeCurrency()));

	QNetworkRequest request(_url);
	_reply = _manager->get(request);
	connect(_reply, &QNetworkReply::finished, this, &RequestAPI::replyFinished);
}

void RequestAPI::replyFinished()
{
	_reply = qobject_cast<QNetworkReply *>(sender());

	if (_reply->error() == QNetworkReply::NoError)
	{
		/*
		    Парсинг полученных данных.
		*/
		QJsonDocument content = QJsonDocument::fromJson(_reply->readAll());
		QJsonObject root = content.object();
		QVariantMap map = root.toVariantMap();
		for (int i = 1; i < _currencyWired.size(); i++)
		{
			for (auto iter = map.begin(); iter != map.end(); iter++)
			{
				if (iter.key().contains(_currencyWired[i]->getTypeCurrency()))
				{
					_currencyWired[i]->setRatioCurrency(map[iter.key()].toDouble());
				}
			}
		}
	}
	_reply->deleteLater();
	emit replyAccepted();
}

QVector<Currency*> RequestAPI::getResultParse() const
{
	return _currencyWired;
}

RequestAPI::~RequestAPI()
{

}