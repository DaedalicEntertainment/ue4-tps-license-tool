#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "About/aboutdialog.h"
#include "About/aboutmodel.h"

#include "Controller/maincontroller.h"

using Daedalic::AboutDialog;
using Daedalic::AboutModel;

MainWindow::MainWindow(MainController* mainController, QWidget *parent) :
    DaedalicMainWindow(parent),
    _mainController(mainController),
    _ui(new Ui::MainWindow),
    _aboutDialog(nullptr)
{
    _ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    if (_aboutDialog == nullptr) {
        // Get model.
        const AboutModel& aboutModel = _mainController->aboutModel();

        // Get icon.
        QIcon applicationIcon(":/Media/Daedalic.ico");
        QPixmap applicationPixmap = applicationIcon.pixmap(64);

        // Create dialog.
        _aboutDialog = QSharedPointer<AboutDialog>::create(aboutModel, applicationPixmap, this);
    }

    showWindow(_aboutDialog);
}
