#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSharedPointer>

class MainWindow;

namespace Daedalic
{
    class AboutModel;
}

class MainController
{
public:
    MainController();

    void start();

    const Daedalic::AboutModel& aboutModel() const;

    static const QString COPYRIGHT_YEAR_STRING;

private:
    MainWindow* _mainWindow;
    QSharedPointer<Daedalic::AboutModel> _aboutModel;
};

#endif // MAINCONTROLLER_H
