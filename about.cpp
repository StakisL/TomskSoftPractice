#include "about.h"


About::About(QDialog *parent) : QDialog(parent)
{
	_textAbout = new QLabel(this);
	_textAbout->setText(tr("Summer practice programm. "
		                  "\nOnline converter. "
		                  "\nThe work was performed by Lebel S.S."));
	
	_button = new QPushButton(tr("Ok"),this);
	connect(_button, &QPushButton::clicked, this, &About::close);

	_mainLayout = new QVBoxLayout(this);
	_mainLayout->addWidget(_textAbout);
	_mainLayout->addWidget(_button);
	setLayout(_mainLayout);

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

About::~About()
{
}
