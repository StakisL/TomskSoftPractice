#include "save_data.h"

SaveData::SaveData()
{
	_fileName = QString("save.json");
}

QJsonDocument SaveData::loadData(const QString &fileName)
{
	_jsonFile.setFileName(fileName);
	auto result = _jsonFile.open(QIODevice::ReadOnly);
	if (!result)
		return QJsonDocument();
	else
		return QJsonDocument().fromJson(_jsonFile.readAll());

	_jsonFile.close();
}

void SaveData::saveData(QJsonDocument &document, const QString &fileName)
{
	_jsonFile.setFileName(fileName);
	auto result = _jsonFile.open(QIODevice::WriteOnly);
	if(!result)
	{
		_errorBox.setText("Error, data not saved!");
		_errorBox.exec();
	}
	else
	{
		_jsonFile.write(document.toJson());
	}
	_jsonFile.close();
}

void SaveData::saveValue(const QMap<CurrenciesPair, double> &currencies, const QDate &date)
{
	_recordArray = QJsonArray();

	_jsonDocument = loadData(_fileName);
	_dateObject = _jsonDocument.object();

	for (int i = 0; i < currencies.size(); i++)
	{
		auto currency = currencies.keys().at(i);
		_recordObject["first"] = currencyTypeToString(currency.first);
		_recordObject["second"] = currencyTypeToString(currency.second);
		_recordObject["ratio"] = currencies[CurrenciesPair(currency.first,
			currency.second)];
		_recordArray.append(_recordObject);
	}
	_dateObject[date.toString("dd.MM.yyyy")] = _recordArray;
	_jsonDocument.setObject(_dateObject);

	saveData(_jsonDocument, _fileName);
}

void SaveData::loadValue(QMap<CurrenciesPair, double> &currencies, const QDate &date)
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
			auto currency = currencies.keys().at(i);
			_recordObject = _recordArray.at(j).toObject();
			if (_recordObject["first"] == currencyTypeToString(currency.first) &&
				_recordObject["second"] == currencyTypeToString(currency.second))
			{
				currencies[CurrenciesPair(currency.first, currency.second)]
					= _recordObject["ratio"].toDouble();
			}
		}
	}
}


bool SaveData::checkData(const QDate &date)
{
	_dateObject = loadData(_fileName).object();

	for (int i = 0; i < _dateObject.size(); i++)
	{
		if (_dateObject.keys().at(i) == date.toString("dd.MM.yyyy"))
			return true;
	}
	return false;
}


SaveData::~SaveData() = default;

