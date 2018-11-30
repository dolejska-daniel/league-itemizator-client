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

    auto data_lastUpdate = settings->value("data/updated_at").toString();
    if (data_lastUpdate.length())
    {
        ui->label_data_lastUpdate->setText(data_lastUpdate);
        ui->label_data_version->setText(settings->value("data/version").toString());
    }

    auto app_lastUpdate = settings->value("app/updated_at").toString();
    if (app_lastUpdate.length())
    {
        ui->label_app_lastUpdate->setText(app_lastUpdate);
        ui->label_app_version->setText(settings->value("app/version").toString());
    }

    //  Connecting signals with slots
    connect(ui->actionAutoUpdate_data, SIGNAL(toggled(bool)), this, SLOT(AutoUpdateData(bool)));
    connect(ui->actionUpdate_data, SIGNAL(triggered()), this, SLOT(UpdateData()));

    connect(ui->actionAutoUpdate_client, SIGNAL(toggled(bool)), this, SLOT(AutoUpdateClient(bool)));
    connect(ui->actionUpdate_client, SIGNAL(triggered()), this, SLOT(UpdateClient()));

    connect(ui->actionSettings, SIGNAL(triggered()), _settingsDialog, SLOT(show()));
    connect(ui->actionAboutApplication, SIGNAL(triggered()), _aboutDialog, SLOT(show()));

    this->show();

    //  Locate League of Legends installation directory
    auto leagueInstallDir = settings->value("install-dir/league", "").toString();
    if (!leagueInstallDir.length())
    {
        this->statusBar()->showMessage("Searching for League...");
        QSysInfo sys;
        if (sys.windowsVersion())
        {
            //  Windows OS, trying to find it on my own
            //  TODO: fix registry path
            QSettings registry("HKEY_LOCAL_MACHINE/...", QSettings::NativeFormat);
            //  TODO: fix registry item key
            leagueInstallDir = registry.value("...", "").toString();
        }

        if (!leagueInstallDir.length())
        {
            //  non-Windows OS / registry key not found - can't find on my own
            QMessageBox::information(this, "Failed to find League!", "Sorry, but this poor program failed to find League of Legends installation directory. You will have to find it yourself.");
            //  TODO: rather select LeagueOfLegends executable?
            leagueInstallDir = QFileDialog::getExistingDirectory(this, "Open 'League of Legends' install directory", "~", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        }

        QDir installDir(leagueInstallDir);
        //  TODO: cd to config dir
        installDir.cd("");
        //  TODO: validate directory (write permissions, etc.)
    }
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}


//======================================================================dd==
//  CONTROL FUNCTIONS
//======================================================================dd==

void MainWindow::GetCurrentDataVersion()
{
    auto version = api->GetCurrentDataVersion();
    ui->label_data_versionLatest->setText(version);
    //  TODO: Validate whether is up-to-date or not
}

void MainWindow::GetCurrentAppVersion()
{
    auto version = api->GetCurrentProgramVersion();
    ui->label_app_versionLatest->setText(version);
    //  TODO: Validate whether is up-to-date or not
}


//======================================================================dd==
//  SLOTS
//======================================================================dd==

void MainWindow::AutoUpdateData(bool value)
{
    settings->setValue("data/auto-updates", value);
}

void MainWindow::UpdateData()
{
    //  TODO: api->GetCurrentData...?
}

void MainWindow::AutoUpdateClient(bool value)
{
    settings->setValue("app/auto-updates", value);
}

void MainWindow::UpdateClient()
{
    //  TODO: api->GetCurrentApp...?
}
