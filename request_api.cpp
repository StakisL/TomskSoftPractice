#include "request_api.h"



RequestAPI::RequestAPI(QNetworkAccessManager *parent) 
	: QNetworkAccessManager(parent)
{
	_manager = new QNetworkAccessManager();
}

void RequestAPI::getRequest(QVector<Currency*> currency, QDate date)
{
	int i = 0; 
	_date = date;
	_currencyWired = currency;
	_url.setUrl(QString("http://free.currconv.com/api/v7/convert?q="
		"%1_%2,%1_%3,%1_%4,%1_%5,%1_%6&compact=ultra&date=%7&apiKey=9942582d9e7fb170c046")
		.arg(_currencyWired[0]->getTypeCurrency()).arg(_currencyWired[1]->getTypeCurrency())
		.arg(_currencyWired[2]->getTypeCurrency()).arg(_currencyWired[3]->getTypeCurrency())
		.arg(_currencyWired[4]->getTypeCurrency()).arg(_currencyWired[5]->getTypeCurrency())
		.arg(date.toString("yyyy-MM-dd")));

	QNetworkRequest request(_url);
	_reply = _manager->get(request);
	connect(_reply, &QNetworkReply::finished, this, &RequestAPI::replyFinished);
}

void RequestAPI::replyFinished()
{
	_reply = qobject_cast<QNetworkReply *>(sender());

	if (_reply->error() == QNetworkReply::NoError)
	{
		QJsonDocument content = QJsonDocument::fromJson(_reply->readAll());
		QJsonObject root = content.object();
		QJsonObject innerRoot;
		for (int i = 1; i < _currencyWired.size(); i++)
		{
			for (int j = 0 ; j < root.size(); j++)
			{
				if (root.keys().at(j).contains(_currencyWired[i]->getTypeCurrency()))
				{
					innerRoot = root[root.keys().at(j)].toObject();
					_currencyWired[i]->setRatioCurrency(innerRoot[_date.toString("yyyy-MM-dd")]
						.toDouble());
				}
			}
		}
		_reply->deleteLater();
		emit replyAccepted();
	}
	else
	{
		emit errorRequest();
	}
	
}

QVector<Currency*> RequestAPI::getResultParse() const
{
	return _currencyWired;
}

RequestAPI::~RequestAPI() {}
