#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    _settings(settings)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}


