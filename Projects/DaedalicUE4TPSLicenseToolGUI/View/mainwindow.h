#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MainController* mainController, QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainController* _mainController;
    Ui::MainWindow* _ui;
};

#endif // MAINWINDOW_H
