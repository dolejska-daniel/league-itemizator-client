#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug>


SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    _settings(settings)
{
    ui->setupUi(this);

    ui->closeToTray->setCheckState(_settings->value("app/close-to-tray", false).toBool() ? Qt::Checked : Qt::Unchecked);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    _settings->setValue("app/close-to-tray", static_cast<bool>(ui->closeToTray->checkState()));

    this->close();
}
