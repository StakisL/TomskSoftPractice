#include "about.h"


About::About(QDialog *parent) : QDialog(parent)
{
	this->setFixedHeight(200);
	this->setFixedWidth(300);

	_textAbout = new QLabel(this);
	_textAbout->setText(tr("\tSummer practice programm.\t"
		                  "\n\tOnline converter currency.\t "
		                  "\n\tThe work was performed by Lebel S.S.\t"));
	_textAbout->setGeometry(5, 5, 200, 200);
	
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
