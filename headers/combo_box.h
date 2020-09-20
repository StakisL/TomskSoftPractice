#ifndef COMBO_BOX_H
#define COMBO_BOX_H

#include <QComboBox>
#include "currency.h"

class ComboBox : public QComboBox
{
	Q_OBJECT

public:
	ComboBox(QComboBox *parent = nullptr);
	~ComboBox();

	CurrencyType currentItem();
};

#endif COMBO_BOX_H

