#include "combo_box.h"



ComboBox::ComboBox(QComboBox *parent) 
	: QComboBox(parent)
{
}

CurrencyType ComboBox::currentItem()
{
	switch (currentIndex())
	{
	case 0:
		return CurrencyType::USD;
	case 1:
		return CurrencyType::AUD;
	case 2:
		return CurrencyType::CAD;
	case 3:
		return CurrencyType::RUB;
	case 4:
		return CurrencyType::JPY;
	case 5:
		return CurrencyType::EUR;
	}
	return CurrencyType::USD;
}

ComboBox::~ComboBox() = default;

