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
#include "Currency.h"

class RequestAPI : public QNetworkAccessManager
{
	Q_OBJECT
public:
	RequestAPI(QNetworkAccessManager *parent = nullptr);
	~RequestAPI();

	QVector<Currency*> getResultParse() const;
	void getRequest(QVector<Currency*> currency, QDate date);

signals:
	void replyAccepted();

private:
	void replyFinished();

	QVector<Currency*> _currencyWired;
	QNetworkAccessManager *_manager;
	QNetworkReply *_reply;
	QUrl _url;
	QDate _date;
};
#endif

