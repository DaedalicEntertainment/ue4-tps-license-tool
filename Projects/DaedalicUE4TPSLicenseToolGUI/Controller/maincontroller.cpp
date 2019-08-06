#include "maincontroller.h"

#include "About/aboutmodel.h"

#include "View/mainwindow.h"

using Daedalic::AboutModel;

const QString MainController::COPYRIGHT_YEAR_STRING = "2019";

MainController::MainController()
    : _mainWindow(new MainWindow(this)),
      _aboutModel(new AboutModel())
{
    _aboutModel->init(COPYRIGHT_YEAR_STRING);
}

void MainController::start()
{
    _mainWindow->show();
}

const Daedalic::AboutModel& MainController::aboutModel() const
{
    return *_aboutModel;
}
