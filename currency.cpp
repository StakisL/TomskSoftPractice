#include "currency.h"



Currency::Currency(QString _typeCurrency)
{
	typeCurrency = _typeCurrency;
	isBase = false;
}

double Currency::getRatioCurrency() const
{
	return ratioCurrency;
}

void Currency::setRatioCurrency(double _ratioCurrency)
{
	ratioCurrency = _ratioCurrency;
}

QString Currency::getTypeCurrency() const
{
	return typeCurrency;
}

void Currency::setTypeCurrency(QString _typeCurrency)
{
	typeCurrency = _typeCurrency;
}

bool Currency::getBase() const
{
	return isBase;
}

void Currency::setBase(bool _isBase)
{
	isBase = _isBase;
}

double Currency::getValue(int value)
{
	return value * ratioCurrency;
}

Currency::~Currency()
{
}
