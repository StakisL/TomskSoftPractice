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

void SaveData::saveData(QMap<CurrenciesPair, double> currencies, QDate date)
{
	_recordArray = QJsonArray();

	_jsonDocument = loadData(_fileName);
	_dateObject = _jsonDocument.object();

	for (int i = 0; i < currencies.size(); i++)
	{
		_recordObject["first"] = currencyTypeToString(currencies.keys().at(i).first);
		_recordObject["second"] = currencyTypeToString(currencies.keys().at(i).second);
		_recordObject["ratio"] = currencies[CurrenciesPair(currencies.keys().at(i).first,
			currencies.keys().at(i).second)];
		_recordArray.append(_recordObject);
	}
	_dateObject[date.toString("dd.MM.yyyy")] = _recordArray;
	_jsonDocument.setObject(_dateObject);

	saveJson(_jsonDocument, _fileName);
}

void SaveData::loadValue(QMap<CurrenciesPair, double> &currencies, QDate date)
{
	_recordArray = QJsonArray();

	_dateObject = loadData(_fileName).object();
	for (int i = 0; i < _dateObject.size(); i++)
	{
		if (_dateObject.keys().at(i) == date.toString("dd.MM.yyyy"))
		{
			_recordArray = _dateObject[_dateObject.keys().at(i)].toArray();
		}
	}

	for (int i = 0; i < currencies.size(); i++)
	{
		for (int j = 0; j < _recordArray.size(); j++)
		{
			_recordObject = _recordArray.at(j).toObject();
			if (_recordObject["first"] == currencyTypeToString(currencies.keys().at(i).first) &&
				_recordObject["second"] == currencyTypeToString(currencies.keys().at(i).second))
			{
				currencies[CurrenciesPair(currencies.keys().at(i).first, currencies.keys().at(i).second)] 
					= _recordObject["ratio"].toDouble();
			}
		}
	}
}


bool SaveData::checkData(QDate date)
{
	_dateObject = loadData(_fileName).object();

	for (int i = 0; i < _dateObject.size(); i++)
	{
		if (_dateObject.keys().at(i) == date.toString("dd.MM.yyyy"))
			return true;
	}
	return false;
}


SaveData::~SaveData()
{
	if (_jsonFile.isOpen())
		_jsonFile.close();
}

