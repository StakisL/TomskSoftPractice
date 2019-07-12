#include "about.h"


About::About(QDialog *parent) : QDialog(parent)
{
	_textAbout = new QLabel(this);
	_textAbout->setText(tr("Summer practice programm. "
		                  "\nOnline converter. "
		                  "\nThe work was performed by Lebel S.S."));
	
	_button = new QPushButton(tr("Ok"),this);
	connect(_button, &QPushButton::clicked, this, &About::close);

<<<<<<< HEAD
	_mainLayout = new QVBoxLayout(this);
	_mainLayout->addWidget(_textAbout);
	_mainLayout->addWidget(_button);
	setLayout(_mainLayout);
=======
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(textAbout);
	mainLayout->addWidget(button);
	setLayout(mainLayout);
>>>>>>> 0ff7d378ef9884527ad3902d65f156881c8e718b

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

About::~About()
{
}
