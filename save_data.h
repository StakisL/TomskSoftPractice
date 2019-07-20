#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QVector>
#include "currency.h"

class SaveData
{
public:
	SaveData();
	~SaveData();

	QJsonDocument loadData(QString fileName);
	void saveJson(QJsonDocument document, QString fileName);

	void saveData(QVector<Currency*> currencyWired, QDate date);
	QVector<Currency*> loadValue(QString baseCurrency, QDate date);
	
	bool checkData(QString baseCurrency, QDate data);

private:
	QFile _jsonFile;

	QTime _oldTime;
	QTime _newTime;
	QString _fileName;

	QVector<Currency*> _currencyWired;

	QDate _date;
};

#endif

