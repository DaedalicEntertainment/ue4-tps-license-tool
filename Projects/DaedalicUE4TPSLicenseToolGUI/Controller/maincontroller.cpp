#include "maincontroller.h"

#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QTextStream>

#include <QXmlStreamReader>

#include "About/aboutmodel.h"

#include "Model/tpsdata.h"
#include "View/mainwindow.h"

using Daedalic::AboutModel;

const QString MainController::COPYRIGHT_YEAR_STRING = "2019";
const QString MainController::SETTINGS_ENGINE_PATH = "EnginePath";
const QString MainController::SETTINGS_TPSAUDITOUTPUT_PATH = "TPSAuditOutputPath";
const QString MainController::SETTINGS_OUTPUT_PATH = "OutputPath";

MainController::MainController()
    : _mainWindow(new MainWindow(this)),
      _aboutModel(new AboutModel())
{
    _aboutModel->init(COPYRIGHT_YEAR_STRING);
}

void MainController::start()
{
    _mainWindow->show();
    _mainWindow->init();
}

void MainController::generateLicenseFile(const QString &enginePath, const QString &tpsAuditOutputPath, const QString &outputPath)
{
    // Save settings.
    QSettings settings;
    settings.setValue(SETTINGS_ENGINE_PATH, enginePath);
    settings.setValue(SETTINGS_TPSAUDITOUTPUT_PATH, tpsAuditOutputPath);
    settings.setValue(SETTINGS_OUTPUT_PATH, outputPath);

    // NOTE(np): Somehow, we're unable to properly call UAT from Qt with arguments.
    //    // Build argument list.
    //    QString workingDirectory = enginePath + "/Engine/Build/BatchFiles";
    //    QString program = "cmd.exe";

    //    QStringList arguments;
    //    arguments << "/C";
    //    arguments << "RunUAT.bat";
    //    arguments << "ListThirdPartySoftware";
    //    arguments << "\"-target=UE4Game|Shipping|Win64\"";
    //    arguments << "\"-target=CrashReportClient|Shipping|Win64\"";
    //    arguments << (">" + outputPath);

    //    // Start UAT.
    //    QProcess process(this);
    //    process.setWorkingDirectory(workingDirectory);
    //    process.setProgram(program);
    //    process.setArguments(arguments);
    //    process.setStandardOutputFile( QProcess::nullDevice() );
    //    process.setStandardErrorFile( QProcess::nullDevice() );
    //    process.startDetached();

    // Parse audit results.
    QFile auditFile(tpsAuditOutputPath);

    if (!auditFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(_mainWindow, "Error", "TPS audit output file can't be opened.");
        return;
    }

    QTextStream textStream(&auditFile);
    QStringList tpsFilePaths;
    QList<TpsData> tpsDataList;

    while (!textStream.atEnd())
    {
        QString line = textStream.readLine();

        // Remove other UAT output.
        if (line.startsWith(enginePath))
        {
            // Remove redirect hints.
            if (line.contains("(redirect from"))
            {
                line = line.split("(redirect from")[0];
            }

            // Remove duplicates.
            if (!tpsFilePaths.contains(line))
            {
                tpsFilePaths << line;

                // Open TPS data file.
                QFile tpsFile(line);
                if (tpsFile.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    TpsData tpsData;

                    QXmlStreamReader xmlStream(&tpsFile);

                    // Read TPS data.
                    while (!xmlStream.atEnd() && !xmlStream.hasError())
                    {
                        QXmlStreamReader::TokenType token = xmlStream.readNext();

                        if (token == QXmlStreamReader::StartElement)
                        {
                            if (xmlStream.name() == "Name")
                            {
                                tpsData.name = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "Location")
                            {
                                tpsData.location = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "Date")
                            {
                                tpsData.date = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "Function")
                            {
                                tpsData.function = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "Justification")
                            {
                                tpsData.justification = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "Eula")
                            {
                                tpsData.eula = xmlStream.readElementText();
                            }
                            else if (xmlStream.name() == "LicenseFolder")
                            {
                                tpsData.licenseFolder = xmlStream.readElementText();
                            }
                        }
                    }

                    tpsDataList << tpsData;
                }
            }
        }
    }

    // Create output file for combined license data.
    QFile outputFile(outputPath);

    if (!outputFile.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(_mainWindow, "Error", "Output file can't be opened.");
        return;
    }

    QTextStream outputStream(&outputFile);

    for (const TpsData& tpsData : tpsDataList)
    {
        // Skip empty TPS licenses.
        if (!tpsData.licenseFolder.isEmpty() && tpsData.licenseFolder != "None")
        {
            QFile licenseFile(enginePath + tpsData.licenseFolder);

            if (licenseFile.open(QIODevice::ReadOnly))
            {
                outputStream << tpsData.name << endl;
                outputStream << endl;

                QTextStream licenseStream(&licenseFile);

                while (!licenseStream.atEnd())
                {
                    outputStream << licenseStream.readLine() << endl;
                }

                outputStream << endl;
                outputStream << endl;
            }
        }
    }
}

const Daedalic::AboutModel& MainController::aboutModel() const
{
    return *_aboutModel;
}

const QString MainController::enginePath() const
{
    return QSettings().value(SETTINGS_ENGINE_PATH).toString();
}

const QString MainController::tpsAuditOutputPath() const
{
    return QSettings().value(SETTINGS_TPSAUDITOUTPUT_PATH).toString();
}

const QString MainController::outputPath() const
{
    return QSettings().value(SETTINGS_OUTPUT_PATH).toString();
}
