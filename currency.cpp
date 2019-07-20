#include "currency.h"

Currency::Currency(QString typeCurrency)
{
	_typeCurrency = typeCurrency;
}

Currency::Currency(QString typeCurrency, double ratioCurrency)
{
	_typeCurrency = typeCurrency;
	_ratioCurrency = ratioCurrency;
}

double Currency::getRatioCurrency() const
{
	return _ratioCurrency;
}

void Currency::setRatioCurrency(double ratioCurrency)
{
	_ratioCurrency = ratioCurrency;
}

QString Currency::getTypeCurrency() const
{
	return _typeCurrency;
}

void Currency::setTypeCurrency(QString typeCurrency)
{
	_typeCurrency = typeCurrency;
}

double Currency::getValue(double value)
{
	return value * _ratioCurrency;
}

Currency::~Currency()
{
}
