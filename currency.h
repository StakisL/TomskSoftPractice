#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>

class Currency
{
public:
	Currency(QString typeCurrency);
	Currency(QString typeCurrency, double ratioCurrency);
	~Currency();

	double getRatioCurrency() const;
	QString getTypeCurrency() const;

	void setRatioCurrency(double _ratioCurrency);
	void setTypeCurrency(QString _typeCurrency);

	double getValue(double value);

private:
	QString _typeCurrency;
	double _ratioCurrency;
};

#endif CURRENCY_H


