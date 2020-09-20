#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>
#include <QPair>
#include <QMap>

enum class CurrencyType
{
	USD,
	AUD,
	CAD,
	RUB,
	JPY,
	EUR
};

typedef QPair<CurrencyType, CurrencyType> CurrenciesPair;

void createCurrencyMap(QMap<CurrenciesPair, double> &currencies);

QString currencyTypeToString(CurrencyType &type);

#endif CURRENCY_H

