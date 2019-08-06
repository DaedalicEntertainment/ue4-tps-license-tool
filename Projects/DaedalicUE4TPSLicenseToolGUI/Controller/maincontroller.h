#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSharedPointer>

class MainWindow;

namespace Daedalic
{
    class AboutModel;
}

class MainController : QObject
{
    Q_OBJECT

public:
    MainController();

    void start();
    void generateLicenseFile(const QString& enginePath, const QString& tpsAuditOutputPath, const QString& outputPath);

    const Daedalic::AboutModel& aboutModel() const;

    const QString enginePath() const;
    const QString tpsAuditOutputPath() const;
    const QString outputPath() const;

    static const QString COPYRIGHT_YEAR_STRING;
    static const QString SETTINGS_ENGINE_PATH;
    static const QString SETTINGS_TPSAUDITOUTPUT_PATH;
    static const QString SETTINGS_OUTPUT_PATH;

private:
    MainWindow* _mainWindow;
    QSharedPointer<Daedalic::AboutModel> _aboutModel;
};

#endif // MAINCONTROLLER_H
