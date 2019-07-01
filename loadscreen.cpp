#include "loadscreen.h"
#include "ui_loadscreen.h"


LoadScreen::LoadScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadScreen)
{
    ui->setupUi(this);
    timer = new QTimer();
    QTimer::singleShot(3000,this,SLOT(closed_LoadScreen()));

}

LoadScreen::~LoadScreen()
{
    delete ui;
}

void LoadScreen::closed_LoadScreen()
{
    window = new Converter(this);
    this->close();
    window->show();
}
