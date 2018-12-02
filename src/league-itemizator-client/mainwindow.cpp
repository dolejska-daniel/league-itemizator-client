#include "aboutdialog.h"
#include "settingsdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QSysInfo>
#include <QAction>

const int APP_VERSION = 1;
const QString APP_VERSION_STRING = "v0.0.1";
const QString APP_VERSION_DATE = "2018-12-02";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    settings(new QSettings("dolejska-daniel", "League Itemizator")),
    api(new DataApi()),
    ui(new Ui::MainWindow),
    _aboutDialog(new AboutDialog(this)),
    _settingsDialog(new SettingsDialog(settings, this))
{
    ui->setupUi(this);

    //  Change UI states according to saved settings
    ui->actionAutoUpdate_data->setChecked(settings->value("data/auto-updates", false).toBool());
    ui->actionAutoUpdate_client->setChecked(settings->value("app/auto-updates", false).toBool());
    DisplayAppVersion();
    DisplayDataVersion();

    //  Connecting signals with slots
    connect(ui->actionAutoUpdate_data, SIGNAL(toggled(bool)), this, SLOT(AutoUpdateData(bool)));
    connect(ui->actionUpdate_data, SIGNAL(triggered()), this, SLOT(UpdateData()));

    connect(ui->actionAutoUpdate_client, SIGNAL(toggled(bool)), this, SLOT(AutoUpdateApp(bool)));
    connect(ui->actionUpdate_client, SIGNAL(triggered()), this, SLOT(UpdateApp()));

    connect(ui->actionSettings, SIGNAL(triggered()), _settingsDialog, SLOT(show()));
    connect(ui->actionAboutApplication, SIGNAL(triggered()), _aboutDialog, SLOT(show()));

    this->show();

    //  Locate League of Legends installation directory
    auto leagueInstallDir = settings->value("install-dir/league", "").toString();
    QDir targetDir;

    while(!targetDir.cd(leagueInstallDir) || !targetDir.exists("Config/Champions"))
    {
        //  Try to find the directory, prompt the user, ...
        this->statusBar()->showMessage("Searching for League...");

        QSysInfo sys;
        if (sys.windowsVersion() && leagueInstallDir.length())
        {
            //  Windows OS, trying to find it on my own
            //  TODO: fix registry path
            QSettings registry("HKEY_LOCAL_MACHINE/...", QSettings::NativeFormat);
            //  TODO: fix registry item key
            leagueInstallDir = registry.value("...", "").toString();
            continue;
        }

        //  non-Windows OS / registry key not found - can't find on my own
        auto questionResult = QMessageBox::question(this, "Failed to find League!", "Failed to load League of Legends installation directory.\nPlease locate the directory.", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (questionResult == QMessageBox::Cancel)
            //  User cancelled prompt
            exit(0);

        //  TODO: rather select LeagueOfLegends executable?
        leagueInstallDir = QFileDialog::getExistingDirectory(this, "Open 'League of Legends' install directory");
    }
    //  Either correct directory was resolved or application has been closed
    settings->setValue("install-dir/league", leagueInstallDir);

    itemsets = new ItemsetApi(targetDir, api);

    //  Download current Data & App
    //  TODO: Set timer to periodically call Update*();
    UpdateApp();
    UpdateData(false);
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}


//======================================================================dd==
//  SETTINGS MODIFICATION FUNCTIONS
//======================================================================dd==

void MainWindow::SetDataVersion(QPair<int, QString> version)
{
    settings->setValue("data/version", version.first);
    settings->setValue("data/version_string", version.second);
    settings->setValue("data/updated_at", QDateTime().toString("yyyy-MM-dd hh:mm"));
    DisplayDataVersion();
}

void MainWindow::SetAppVersion(QPair<int, QString> version)
{
    //  TODO: ?
}


//======================================================================dd==
//  UI MODIFICATION FUNCTIONS
//======================================================================dd==

void MainWindow::DisplayDataVersion()
{
    ui->label_data_version->setText(settings->value("data/version_string", unknownText).toString());
    auto lastUpdate = settings->value("data/updated_at", "").toString();
    if (lastUpdate.length())
    {
        ui->label_data_lastUpdate->setText(lastUpdate);
        ui->label_data_version->setText(settings->value("data/version_string").toString());
    }
}

void MainWindow::DisplayAppVersion()
{
    ui->label_app_version->setText(APP_VERSION_STRING);
    ui->label_app_lastUpdate->setText(APP_VERSION_DATE);
}


//======================================================================dd==
//  SLOTS
//======================================================================dd==

void MainWindow::AutoUpdateData(bool value)
{
    settings->setValue("data/auto-updates", value);
}

void MainWindow::UpdateData(bool force)
{
    this->statusBar()->showMessage("Fetching current Data version...");
    auto version = api->GetCurrentDataVersion();
    ui->label_data_versionLatest->setText(version.second);
    if (settings->value("data/version", 0).toInt() == version.first && !force)
    {
        qInfo() << "Data are up-to-date.";
        ui->label_data_upToDate->setText(yesText);
        this->statusBar()->showMessage("Data up-to-date!", 5);
    }
    else
    {
        qInfo() << "Data are outdated.";
        this->statusBar()->showMessage("Downloading new itemsets...");
        ui->label_data_upToDate->setText(noText);

        //  Get list of itemset files
        auto files = api->GetFileList();
        //  Remove old itemsets
        itemsets->RemoveAll();
        //  Save files
        //  TODO: Display progress
        itemsets->Save(files);
        //  Update current Data version
        SetDataVersion(version);
        UpdateData(false);
    }
}

void MainWindow::AutoUpdateApp(bool value)
{
    settings->setValue("app/auto-updates", value);
}

void MainWindow::UpdateApp()
{
    this->statusBar()->showMessage("Fetching current App version...");
    auto version = api->GetCurrentProgramVersion();
    ui->label_app_versionLatest->setText(version.second);
    if (APP_VERSION == version.first)
    {
        qInfo() << "App is up-to-date.";
        ui->label_app_upToDate->setText(yesText);
        this->statusBar()->showMessage("App up-to-date!", 5);
    }
    else
    {
        qInfo() << "App is outdated.";
        ui->label_app_upToDate->setText(noText);
        this->statusBar()->showMessage("App update not is yet supported.", 8);
        //  TODO: If auto-update is allowed, update
    }
}