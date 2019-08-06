#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainController* mainController, QWidget *parent) :
    QMainWindow(parent),
    _mainController(mainController),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
