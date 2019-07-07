#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>

/*
    Класс описывает валюты и ее состояния.
	typeCurrency - Тип валюты(рублы,доллары и т.д.)
	ratioCurrency - Коэффициент валюты относительно базовой
	isBase - true если валюта базовая.
*/
class Currency
{
public:
	Currency(QString _typeCurrency);
	double getRatioCurrency() const;
	QString getTypeCurrency() const;
	bool getBase() const;
	void setRatioCurrency(double _ratioCurrency);
	void setTypeCurrency(QString _typeCurrency);
	void setBase(bool _isBase);
	~Currency();

private:
	QString typeCurrency;
	double ratioCurrency;
	bool isBase;
};

#endif CURRENCY_H

