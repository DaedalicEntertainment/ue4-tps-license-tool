#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

class MainWindow;

class MainController
{
public:
    MainController();

    void start();

private:
    MainWindow* _mainWindow;
};

#endif // MAINCONTROLLER_H
