#ifndef REQUEST_API_H
#define REQUEST_API_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QString>
#include <QDate>
#include <QPair>
#include <QQueue>
#include "Currency.h"

class RequestAPI : public QNetworkAccessManager
{
	Q_OBJECT
public:
	RequestAPI(QMap<CurrenciesPair, double> currencies, QNetworkAccessManager *parent = nullptr);
	~RequestAPI();

	QMap<CurrenciesPair, double> getResultParse();
	void getRequest(QDate date);
	

signals:
	void replyAccepted();

private:
	void replyFinished();
	void makeRequest(QUrl url);

	QNetworkAccessManager *_manager;
	QNetworkReply *_reply;

	QMap<CurrenciesPair, double> _currencies;

	QQueue<QJsonObject> _resultRequest;

	QUrl _urlFirst;
	QUrl _urlSecond;
	QUrl _urlThird;

	QDate _date;

	int  _countRequestSignals;
	
};
#endif

