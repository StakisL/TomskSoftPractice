#include "currency.h"

void createCurrencyMap(QMap<CurrenciesPair, double> &currencies)
{
	const int countCurrency = 6;
	
	for (int i = 0; i < countCurrency; i++)
	{
		for (int j = 0; j < countCurrency; j++)
		{
			if (i != j)
			{
				currencies.insert(CurrenciesPair(CurrencyType(i), 
					CurrencyType(j)), 0.0);
			}
		}
	}
	
}


QString currencyTypeToString(CurrencyType &type)
{
	switch (type)
	{
	case CurrencyType::USD:
		return "USD";

	case CurrencyType::EUR:
		return "EUR";

	case CurrencyType::AUD:
		return "AUD";

	case CurrencyType::CAD:
		return "CAD";

	case CurrencyType::JPY:
		return "JPY";

	case CurrencyType::RUB:
		return "RUB";
	}
	return 0;
}