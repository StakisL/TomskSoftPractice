#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>

/*
    ����� ��������� ������ � �� ���������.
	typeCurrency - ��� ������(�����,������� � �.�.)
	ratioCurrency - ����������� ������ ������������ �������
	isBase - true ���� ������ �������.
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


	double getValue(double value);
=======
	double getValue(int value);
	~Currency();
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

private:
	QString _typeCurrency;
	double _ratioCurrency;
	bool _isBase;
};

#endif CURRENCY_H


