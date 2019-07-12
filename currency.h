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
	~Currency();

	double getRatioCurrency() const;
	QString getTypeCurrency() const;
	bool getBase() const;

	void setRatioCurrency(double _ratioCurrency);
	void setTypeCurrency(QString _typeCurrency);
	void setBase(bool _isBase);
<<<<<<< HEAD
<<<<<<< HEAD


	double getValue(double value);
=======
=======
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b
	double getValue(int value);
	~Currency();
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

private:
	QString _typeCurrency;
	double _ratioCurrency;
	bool _isBase;
};

#endif CURRENCY_H


