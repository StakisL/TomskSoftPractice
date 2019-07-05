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
	double getRatioCurrency();
	double setRatioCurrency(double _ratioCurrency);
	QString getTypeCurrency();
	QString setTypeCurrency(QString _typeCurrency);
	bool getBase();
	bool setBase(bool _isBase);
	~Currency();

private:
	QString typeCurrency;
	double ratioCurrency;
	bool isBase;
};

#endif CURRENCY_H

