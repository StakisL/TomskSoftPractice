#include "parse.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

RequestAPI::RequestAPI(QVector<Currency*> currency, QNetworkAccessManager *parent) 
	: QNetworkAccessManager(parent)
{
	currencyWired = currency;
	manager = new QNetworkAccessManager();
	url.setUrl("http://openexchangerates.org/api/latest.json?app_id=14b15df28cc54c29bc2669d50043b83b");
}

void RequestAPI::getRequest()
{
	QNetworkRequest request(url);
	reply = manager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void RequestAPI::replyFinished()
{
	reply = qobject_cast<QNetworkReply *>(sender());

	if (reply->error() == QNetworkReply::NoError)
	{
		/*
		    Парсинг полученных данных.
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
				}
			}
		}
	}
	reply->deleteLater();
}

QVector<Currency*> RequestAPI::getResultParse() const
{
	return currencyWired;
}

RequestAPI::~RequestAPI()
{

}