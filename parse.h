#ifndef PARSE_H
#define PARSE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include "Currency.h"

class RequestAPI : public QNetworkAccessManager
{
	Q_OBJECT
public:
	RequestAPI(QVector<Currency*> currency, QNetworkAccessManager *parent = 0);
	QVector<Currency*> getResultParse() const;
	void getRequest();
	~RequestAPI();
private:
	QVector<Currency*> currencyWired;
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	QUrl url;
private slots:
	void replyFinished();

};
#endif
