#include <QLayout>
#include <QtWidgets>
#include "widget.h"
#include "about.h"

Widget::Widget()
{
	createFormGroupBox();
	createGridGroupBox();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(formGroupBox);
	mainLayout->addWidget(gridGroupBox);
	setLayout(mainLayout);
}


void Widget::createGridGroupBox()
{
	gridGroupBox = new QGroupBox(tr("Result convert"));
	QGridLayout *layout = new QGridLayout;
	
	for (int i = 0; i < NumGridRows; ++i)
	{
		firstCollums[i] = new QLabel(tr("Currency %1:").arg(i + 1));
		layout->addWidget(firstCollums[i], i + 1, 1);
	}

	for (int i = 0; i < NumGridRows; ++i) 
	{
		secondCollums[i] = new QLabel(tr("Value :").arg(i + 1));
		layout->addWidget(secondCollums[i], i + 1, 2);
	}

	layout->setHorizontalSpacing(50);
	layout->setColumnStretch(1, 10);
	layout->setColumnStretch(2, 20);
	gridGroupBox->setLayout(layout);
}

void Widget::createFormGroupBox()
{
	formGroupBox = new QGroupBox(tr("Date"));
	formGroupBox->setFixedHeight(100);
	QFormLayout *layout = new QFormLayout;


	aboutButton = new QPushButton("About");
	submitButton = new QPushButton("Submit");
	
	valueLabel = new QLabel(tr("Value:"));
	currencyLabel = new QLabel(tr("Currency:"));

	valueEdit = new QLineEdit();
	currencyBox = new QComboBox();

	layout->addRow(valueLabel, valueEdit);
	layout->addRow(currencyLabel, currencyBox);
	layout->addRow(aboutButton,submitButton);
	formGroupBox->setLayout(layout);

	connect(aboutButton, SIGNAL(clicked()), this, SLOT(createWindow()));
	//connect(submitButton, SIGNAL(clicked()), this, SLOT(sendData()));
	
}

void Widget::createWindow()
{
	About about;
	about.exec();
}

Widget::~Widget()
{
}
