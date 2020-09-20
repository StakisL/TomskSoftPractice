#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QMessageBox>
#include <QVector>
#include "currency.h"

class SaveData
{
public:
	SaveData();
	~SaveData();

	void saveValue(const QMap<CurrenciesPair, double> &currencies, const QDate &date);
    void loadValue(QMap<CurrenciesPair, double> &currencies, const QDate &date);
	
	bool checkData(const QDate &data);

private:
	QJsonDocument loadData(const QString &fileName);
	void saveData(QJsonDocument &document, const QString &fileName);

	QFile _jsonFile;

	QString _fileName;

	QJsonObject _dateObject;
	QJsonObject _recordObject;
	QJsonArray _recordArray;

	QMessageBox _errorBox;

	QJsonDocument _jsonDocument;
};

#endif

