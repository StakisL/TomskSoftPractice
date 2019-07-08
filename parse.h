#ifndef PARSE_H
#define PARSE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include "Currency.h"

class Parse : public QNetworkAccessManager
{
	Q_OBJECT
public:
	Parse(QVector<Currency*> currency, QNetworkAccessManager *parent = 0);
	QVector<Currency*> getResultParse() const;
	~Parse();
private:
	QVector<Currency*> currencyWired;
	QNetworkAccessManager *manager;
	QNetworkRequest *request;
	QNetworkReply *reply;

private slots:
	void replyFinished();

};
#endif
