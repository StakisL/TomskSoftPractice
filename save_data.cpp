#include "save_data.h"

SaveData::SaveData()
{
	_fileName = QString("save.json");
}

QJsonDocument SaveData::loadData(QString fileName)
{
	_jsonFile.setFileName(fileName);
	_jsonFile.open(QIODevice::ReadOnly);
	return QJsonDocument().fromJson(_jsonFile.readAll());
}

void SaveData::saveJson(QJsonDocument document, QString fileName)
{
	_jsonFile.setFileName(fileName);
	_jsonFile.open(QIODevice::WriteOnly);
	_jsonFile.write(document.toJson());
	_jsonFile.close();
}

void SaveData::saveData(QVector<Currency*> currencyWired, QDate date)
{
	_currencyWired = currencyWired;
	_date = date;

	QJsonArray resultRequestArray;
	QJsonObject resultRequest;
	QJsonDocument _jsonDocument;

	_jsonDocument = loadData(_fileName);

	resultRequestArray = _jsonDocument.array();

	resultRequest["ABase"] = _currencyWired[0]->getTypeCurrency();
	resultRequest[date.toString("dd.MM.yyyy")] = QTime::currentTime()
		.toString();

	for (int i = 1; i < _currencyWired.size(); i++)
	{
		resultRequest.insert(_currencyWired[i]->getTypeCurrency()
			, _currencyWired[i]->getRatioCurrency());
	}

	resultRequestArray.push_back(resultRequest);
	_jsonDocument.setArray(resultRequestArray);

	saveJson(_jsonDocument, _fileName);
}

QVector<Currency*> SaveData::loadValue(QString baseCurrency, QDate date)
{
	QJsonArray arrayData;
	QJsonObject objectData;

	_currencyWired.clear();

	arrayData = loadData(_fileName).array();

	for (int i = 0; i < arrayData.size(); i++)
	{
		objectData = arrayData.at(i).toObject();
		if (objectData.keys().at(0) == date.toString("dd.MM.yyyy"))
		{
			if (objectData[objectData.keys().at(1)].toString() ==
				baseCurrency)
			{
				if (date == QDate::currentDate())
				{
					if (_oldTime == QTime::fromString
					(objectData[objectData.keys().at(0)].toString()))
					{
						_currencyWired.push_back(new Currency(baseCurrency, 1.0));
						for (int i = 2; i < objectData.size(); i++)
						{
							_currencyWired.push_back(new Currency(objectData.keys().at(i)
								, objectData[objectData.keys().at(i)].toDouble()));
						}
						break;
					}
				}
				else
				{
					_currencyWired.push_back(new Currency(baseCurrency, 1.0));
					for (int i = 2; i < objectData.size(); i++)
					{
						_currencyWired.push_back(new Currency(objectData.keys().at(i)
							, objectData[objectData.keys().at(i)].toDouble()));
					}
					break;
				}
			}
		}
	}
	return _currencyWired;
}

bool SaveData::checkData(QString baseCurrency, QDate date)
{
	QJsonArray arrayData;
	QJsonObject objectData;
	QJsonObject valueData;

	arrayData = loadData(_fileName).array();

	bool result = false;

	for (int i = 0; i < arrayData.size(); i++)
	{
		objectData = arrayData.at(i).toObject();
		if (objectData.keys().at(0) == date.toString("dd.MM.yyyy"))
		{
			if (objectData[objectData.keys().at(1)].toString() == 
				baseCurrency)
			{
				if (date == QDate::currentDate())
				{
					_oldTime = _oldTime.fromString(objectData[objectData.keys().at(0)]
						.toString());;
					_newTime = _newTime.currentTime();
					/*Узнаем сколько милисеккунд прошло с последнего запроса
					В 1 часу = 3600000 msec*/
					int passedTime = (_newTime.hour() * 60 + _newTime.minute())
						- (_oldTime.hour() * 60 + _oldTime.minute());
					if (passedTime > 60 || passedTime > -60)
					{
						result = false;
					}
					result = true;
				}
				else
				{
					result = true;
				}
			}
		}
	}
	return result;
}


SaveData::~SaveData()
{
	if (_jsonFile.isOpen())
		_jsonFile.close();
}

