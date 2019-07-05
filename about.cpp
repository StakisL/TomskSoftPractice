#include "about.h"
#include <QLayout>
#include <QtWidgets>

About::About(QDialog *parent) : QDialog(parent)
{
	textAbout = new QLabel;
	textAbout->setText(tr("Summer practice programm. "
		                  "\nOnline converter. "
		                  "\nThe work was performed by Lebel S.S."));
	
	button = new QPushButton(tr("Ok"));
	connect(button, SIGNAL(clicked()), this, SLOT(close()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(textAbout);
	mainLayout->addWidget(button);
	setLayout(mainLayout);

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

About::~About()
{
	if (button != nullptr)
		delete button;
	if (textAbout != nullptr)
		delete textAbout;
}
