#include "loadscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadScreen w;
    w.show();

    return a.exec();
}
