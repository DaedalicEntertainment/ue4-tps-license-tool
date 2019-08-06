#include <QApplication>

#include "Controller/maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Daedalic UE4 TPS License Tool");
    a.setOrganizationName("Daedalic Entertainment GmbH");

    MainController c;
    c.start();

    return a.exec();
}
