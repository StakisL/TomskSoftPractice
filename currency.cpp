#include "currency.h"



Currency::Currency(QString _typeCurrency)
{
	typeCurrency = _typeCurrency;
}

double Currency::getRatioCurrency()
{
	return ratioCurrency;
}

double Currency::setRatioCurrency(double _ratioCurrency)
{
	ratioCurrency = _ratioCurrency;
}

QString Currency::getTypeCurrency()
{
	return typeCurrency;
}

QString Currency::setTypeCurrency(QString _typeCurrency)
{
	typeCurrency = _typeCurrency;
}

bool Currency::getBase()
{
	return isBase;
}

bool Currency::setBase(bool _isBase)
{
	isBase = _isBase;
}

Currency::~Currency()
{
}
