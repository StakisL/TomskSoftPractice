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
#include "currency.h"

class RequestManager : public QNetworkAccessManager
{
	Q_OBJECT
public:
	RequestManager(QObject *parent = nullptr);
	~RequestManager();

	void getResultParse(QMap<CurrenciesPair, double> &currencies);
	void getRequest(const QDate &date);
	

signals:
	void replyAccepted();
	void replyError(const QString &error);

private:
	void replyFinished();

	void makeRequest(const QUrl &url);

	QNetworkReply *_reply;

	QQueue<QJsonObject> _resultRequest;

	QUrl _urlFirst;
	QUrl _urlSecond;
	QUrl _urlThird;

	QString _textError;

	QDate _date;

	int  _countRequestSignals;
	bool _error;
};
#endif

