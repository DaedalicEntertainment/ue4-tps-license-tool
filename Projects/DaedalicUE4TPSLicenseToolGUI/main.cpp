#include <QApplication>

#include "Controller/maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController c;
    c.start();

    return a.exec();
}
