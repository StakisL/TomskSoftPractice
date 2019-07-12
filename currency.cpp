#include "currency.h"

Currency::Currency(QString typeCurrency)
{
<<<<<<< HEAD
	_typeCurrency = typeCurrency;
	_isBase = false;
=======
	typeCurrency = _typeCurrency;
	isBase = false;
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
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

bool Currency::getBase() const
{
	return _isBase;
}

void Currency::setBase(bool isBase)
{
	_isBase = isBase;
}

double Currency::getValue(double value)
{
	return value * _ratioCurrency;
}

double Currency::getValue(int value)
{
	return value * ratioCurrency;
}

Currency::~Currency()
{
}
