<<<<<<< HEAD
<<<<<<< HEAD
#ifndef REQUEST_API_H
#define REQUEST_API_H
=======
#ifndef PARSE_H
#define PARSE_H
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
=======
#ifndef PARSE_H
#define PARSE_H
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

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
<<<<<<< HEAD
<<<<<<< HEAD
	RequestAPI(QVector<Currency*> currency, QNetworkAccessManager *parent = nullptr);
	~RequestAPI();

	QVector<Currency*> getResultParse() const;
	void getRequest();

signals:
	void replyAccepted();

private:
	void replyFinished();

	QVector<Currency*> _currencyWired;
	QNetworkAccessManager *_manager;
	QNetworkReply *_reply;
	QUrl _url;
	

};
#endif

=======
=======
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
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
signals:
	void replyAccepted();

};
#endif
<<<<<<< HEAD
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
=======
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
