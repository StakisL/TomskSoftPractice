<<<<<<< HEAD
#include "request_api.h"
=======
#include "parse.h"
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
<<<<<<< HEAD
=======
#include <QEventLoop>
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

RequestAPI::RequestAPI(QVector<Currency*> currency, QNetworkAccessManager *parent) 
	: QNetworkAccessManager(parent)
{
<<<<<<< HEAD
	_currencyWired = currency;
	_manager = new QNetworkAccessManager();
	_url.setUrl("http://openexchangerates.org/api/latest.json?app_id=14b15df28cc54c29bc2669d50043b83b");
=======
	currencyWired = currency;
	manager = new QNetworkAccessManager();
	url.setUrl("http://openexchangerates.org/api/latest.json?app_id=14b15df28cc54c29bc2669d50043b83b");
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
}

void RequestAPI::getRequest()
{
<<<<<<< HEAD
	QNetworkRequest request(_url);
	_reply = _manager->get(request);
	connect(_reply, &QNetworkReply::finished, this, &RequestAPI::replyFinished);
=======
	QNetworkRequest request(url);
	reply = manager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
	
	
}

void RequestAPI::replyFinished()
{
<<<<<<< HEAD
	_reply = qobject_cast<QNetworkReply *>(sender());

	if (_reply->error() == QNetworkReply::NoError)
	{
		/*
		    Ïàðñèíã ïîëó÷åííûõ äàííûõ.
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
=======
	reply = qobject_cast<QNetworkReply *>(sender());

	if (reply->error() == QNetworkReply::NoError)
	{
		/*
		    ÃÃ Ã°Ã±Ã¨Ã­Ã£ Ã¯Ã®Ã«Ã³Ã·Ã¥Ã­Ã­Ã»Ãµ Ã¤Ã Ã­Ã­Ã»Ãµ.
		*/
		QJsonDocument content = QJsonDocument::fromJson(reply->readAll());
		QJsonObject root = content.object();
		QJsonObject newroot(root["rates"].toObject());
		QVariantMap map = newroot.toVariantMap();
		for (int i = 0; i < currencyWired.size(); i++)
		{
			for (auto iter = map.begin(); iter != map.end(); ++iter)
			{
				if ((currencyWired[i]->getTypeCurrency()) == iter.key())
				{
					currencyWired[i]->setRatioCurrency(map[iter.key()].toDouble());
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
				}
			}
		}
	}
<<<<<<< HEAD
	_reply->deleteLater();
=======
	reply->deleteLater();
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
	emit replyAccepted();
}

QVector<Currency*> RequestAPI::getResultParse() const
{
<<<<<<< HEAD
	return _currencyWired;
=======
	return currencyWired;
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
}

RequestAPI::~RequestAPI()
{

<<<<<<< HEAD
}
=======
}
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
