#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MainWindow/daedalicmainwindow.h"

namespace Daedalic
{
    class AboutDialog;
}

class MainController;

namespace Ui {
class MainWindow;
}

class MainWindow : public Daedalic::DaedalicMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MainController* mainController, QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_pushButtonGenerateLicenseFile_clicked();

private:
    MainController* _mainController;
    Ui::MainWindow* _ui;
    QSharedPointer<Daedalic::AboutDialog> _aboutDialog;

};

#endif // MAINWINDOW_H
