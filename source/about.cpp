#include "about.h"


About::About(QDialog *parent) : QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	_textAbout = new QLabel(this);
	_textAbout->setText(tr("\tSummer practice programm.\t"
		                  "\n\tOnline converter currency.\t "
		                  "\n\tThe work was performed by Lebel S.S.\t"));
	
	_button = new QPushButton(tr("Ok"),this);
	connect(_button, &QPushButton::clicked, this, &About::close);

	_mainLayout = new QVBoxLayout(this);
	_mainLayout->addWidget(_textAbout);
	_mainLayout->addWidget(_button);
	setLayout(_mainLayout);

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

About::~About() = default;
