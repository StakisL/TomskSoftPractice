#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <QMainWindow>
#include "converter.h"
#include <Qtimer>

namespace Ui {
class LoadScreen;
}

class LoadScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadScreen(QWidget *parent = nullptr);
    ~LoadScreen();

private slots:
    void closed_LoadScreen();

private:
    Ui::LoadScreen *ui;
    Converter *window;
    QTimer *timer;
};

#endif // LOADSCREEN_H
