#include "maincontroller.h"

#include "View/mainwindow.h"

MainController::MainController()
    : _mainWindow(new MainWindow(this))
{
}

void MainController::start()
{
    _mainWindow->show();
}
