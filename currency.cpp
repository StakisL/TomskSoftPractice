#include "currency.h"

QMap<CurrenciesPair, double> init()
{
	QMap<CurrenciesPair, double> currencies;

	currencies.insert(CurrenciesPair(CurrencyType::USD, CurrencyType::EUR), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::USD, CurrencyType::AUD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::USD, CurrencyType::CAD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::USD, CurrencyType::JPY), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::USD, CurrencyType::RUB), 0.0);

	currencies.insert(CurrenciesPair(CurrencyType::RUB, CurrencyType::EUR), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::RUB, CurrencyType::AUD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::RUB, CurrencyType::CAD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::RUB, CurrencyType::JPY), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::RUB, CurrencyType::USD), 0.0);

	currencies.insert(CurrenciesPair(CurrencyType::AUD, CurrencyType::EUR), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::AUD, CurrencyType::USD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::AUD, CurrencyType::CAD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::AUD, CurrencyType::JPY), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::AUD, CurrencyType::RUB), 0.0);

	currencies.insert(CurrenciesPair(CurrencyType::CAD, CurrencyType::EUR), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::CAD, CurrencyType::AUD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::CAD, CurrencyType::USD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::CAD, CurrencyType::JPY), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::CAD, CurrencyType::RUB), 0.0);

	currencies.insert(CurrenciesPair(CurrencyType::EUR, CurrencyType::USD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::EUR, CurrencyType::AUD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::EUR, CurrencyType::CAD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::EUR, CurrencyType::JPY), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::EUR, CurrencyType::RUB), 0.0);

	currencies.insert(CurrenciesPair(CurrencyType::JPY, CurrencyType::EUR), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::JPY, CurrencyType::AUD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::JPY, CurrencyType::CAD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::JPY, CurrencyType::USD), 0.0);
	currencies.insert(CurrenciesPair(CurrencyType::JPY, CurrencyType::RUB), 0.0);

	return currencies;
}


QString currencyTypeToString(CurrencyType type)
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