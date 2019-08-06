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

void MainWindow::init()
{
    _ui->lineEditUnrealEnginePath->setText(_mainController->enginePath());
    _ui->lineEditTPSAuditOutputPath->setText(_mainController->tpsAuditOutputPath());
    _ui->lineEditOutputFilePath->setText(_mainController->outputPath());
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

void MainWindow::on_pushButtonGenerateLicenseFile_clicked()
{
    _mainController->generateLicenseFile(_ui->lineEditUnrealEnginePath->text(),
                                         _ui->lineEditTPSAuditOutputPath->text(),
                                         _ui->lineEditOutputFilePath->text());
}
