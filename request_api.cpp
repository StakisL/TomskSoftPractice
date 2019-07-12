#include "request_api.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

RequestAPI::RequestAPI(QVector<Currency*> currency, QNetworkAccessManager *parent) 
	: QNetworkAccessManager(parent)
{
	_currencyWired = currency;
	_manager = new QNetworkAccessManager();
	_url.setUrl("http://openexchangerates.org/api/latest.json?app_id=14b15df28cc54c29bc2669d50043b83b");
}

void RequestAPI::getRequest()
{
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
		QJsonObject newroot(root["rates"].toObject());
		QVariantMap map = newroot.toVariantMap();
		for (int i = 0; i < _currencyWired.size(); i++)
		{
			for (auto iter = map.begin(); iter != map.end(); ++iter)
			{
				if ((_currencyWired[i]->getTypeCurrency()) == iter.key())
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