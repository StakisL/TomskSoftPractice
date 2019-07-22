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

	void saveData(QMap<CurrenciesPair, double> currencies, QDate date);
    void loadValue(QMap<CurrenciesPair, double> &currencies, QDate date);
	
	bool checkData(QDate data);

private:
	QFile _jsonFile;

	QString _fileName;

	QJsonObject _dateObject;
	QJsonObject _recordObject;
	QJsonArray _recordArray;

	QJsonDocument _jsonDocument;

	QMap<CurrenciesPair, double> _currencies;

	QDate _date;
};

#endif

